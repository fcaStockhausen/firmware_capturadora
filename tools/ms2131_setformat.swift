import AVFoundation
import CoreMedia

let discovery = AVCaptureDevice.DiscoverySession(deviceTypes: [.external], mediaType: .video, position: .unspecified)
guard let device = discovery.devices.first(where: { $0.localizedName.contains("USB3") }) else {
    FileHandle.standardError.write("capturadora no encontrada\n".data(using: .utf8)!)
    exit(1)
}

if CommandLine.arguments.contains("--status") {
    print("formato activo: \(device.activeFormat)")
    exit(0)
}

// buscar el formato 1920x1080 yuvs y su max fps
var best: AVCaptureDevice.Format? = nil
var bestRate: AVFrameRateRange? = nil
for f in device.formats {
    let d = CMVideoFormatDescriptionGetDimensions(f.formatDescription)
    if d.width == 1920 && d.height == 1080 {
        for r in f.videoSupportedFrameRateRanges where r.maxFrameRate >= 60 {
            if best == nil || r.maxFrameRate > (bestRate?.maxFrameRate ?? 0) {
                best = f; bestRate = r
            }
        }
    }
}
guard let fmt = best, let range = bestRate else {
    FileHandle.standardError.write("formato 1920x1080 no encontrado\n".data(using: .utf8)!)
    exit(1)
}

do {
    try device.lockForConfiguration()
    device.activeFormat = fmt
    device.activeVideoMinFrameDuration = range.minFrameDuration
    device.activeVideoMaxFrameDuration = range.minFrameDuration
    device.unlockForConfiguration()
    print("formato activo fijado: 1920x1080 @ \(1.0 / range.minFrameDuration.seconds)x \(fmt)")
} catch {
    FileHandle.standardError.write("error: \(error)\n".data(using: .utf8)!)
    exit(1)
}
