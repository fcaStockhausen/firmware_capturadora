#!/usr/bin/env python3
"""Desensamblador 8051 minimalista para analizar el firmware MS2131."""
import sys

# tabla: opcode -> (mnemonico, tipo_operando)
# tipos: '' none, 'd' direct, 'i' immediate(#), 'r' relativo(salto), 'a' abs11,
#        'A' abs16, 'b' bit, '/b' complement bit, '@ri' indirecto, 'rn' registro,
#        'x' intercambio (d,#), 'j' (bit,rel), 'c' (code addr 16), 's' (d,rel)
T = {}
def e(op, m, t=''): T[op] = (m, t)

e(0x00,'NOP'); e(0x01,'AJMP','a'); e(0x02,'LJMP','A'); e(0x03,'RR A')
e(0x04,'INC A'); e(0x05,'INC','d'); e(0x06,'INC','@r0'); e(0x07,'INC','@r1')
for i in range(8): e(0x08+i,'INC',f'r{i}')
e(0x10,'JBC','j'); e(0x11,'ACALL','a'); e(0x12,'LCALL','A'); e(0x13,'RRC A')
e(0x14,'DEC A'); e(0x15,'DEC','d'); e(0x16,'DEC','@r0'); e(0x17,'DEC','@r1')
for i in range(8): e(0x18+i,'DEC',f'r{i}')
e(0x20,'JB','j'); e(0x21,'AJMP','a'); e(0x22,'RET'); e(0x23,'RL A')
e(0x24,'ADD A,','i'); e(0x25,'ADD A,','d'); e(0x26,'ADD A,','@r0'); e(0x27,'ADD A,','@r1')
for i in range(8): e(0x28+i,'ADD A,',f'r{i}')
e(0x30,'JNB','j'); e(0x31,'ACALL','a'); e(0x32,'RETI'); e(0x33,'RLC A')
e(0x34,'ADDC A,','i'); e(0x35,'ADDC A,','d'); e(0x36,'ADDC A,','@r0'); e(0x37,'ADDC A,','@r1')
for i in range(8): e(0x38+i,'ADDC A,',f'r{i}')
e(0x40,'JC','r'); e(0x41,'AJMP','a'); e(0x42,'ORL','x'); e(0x43,'ORL','x!')
e(0x44,'ORL A,','i'); e(0x45,'ORL A,','d'); e(0x46,'ORL A,','@r0'); e(0x47,'ORL A,','@r1')
for i in range(8): e(0x48+i,'ORL A,',f'r{i}')
e(0x50,'JNC','r'); e(0x51,'ACALL','a'); e(0x52,'ANL','x'); e(0x53,'ANL','x!')
e(0x54,'ANL A,','i'); e(0x55,'ANL A,','d'); e(0x56,'ANL A,','@r0'); e(0x57,'ANL A,','@r1')
for i in range(8): e(0x58+i,'ANL A,',f'r{i}')
e(0x60,'JZ','r'); e(0x61,'AJMP','a'); e(0x62,'XRL','x'); e(0x63,'XRL','x!')
e(0x64,'XRL A,','i'); e(0x65,'XRL A,','d'); e(0x66,'XRL A,','@r0'); e(0x67,'XRL A,','@r1')
for i in range(8): e(0x68+i,'XRL A,',f'r{i}')
e(0x70,'JNZ','r'); e(0x71,'ACALL','a'); e(0x72,'ORL C,','b'); e(0x73,'JMP @A+DPTR')
e(0x74,'MOV A,','i'); e(0x75,'MOV','d=i'); e(0x76,'MOV','@r0=i'); e(0x77,'MOV','@r1=i')
for i in range(8): e(0x78+i,'MOV',f'r{i}=i')
e(0x80,'SJMP','r'); e(0x81,'AJMP','a'); e(0x82,'ANL C,','b'); e(0x83,'MOVC A,@A+PC')
e(0x84,'DIV AB'); e(0x85,'MOV','d=d'); e(0x86,'MOV','@r0,d'); e(0x87,'MOV','@r1,d')
for i in range(8): e(0x88+i,'MOV',f'r{i}=d')
e(0x90,'MOV DPTR,','i16'); e(0x91,'ACALL','a'); e(0x92,'MOV','bd')  # MOV bit,C
e(0x93,'MOVC A,@A+DPTR'); e(0x94,'SUBB A,','i'); e(0x95,'SUBB A,','d')
e(0x96,'SUBB A,','@r0'); e(0x97,'SUBB A,','@r1')
for i in range(8): e(0x98+i,'SUBB A,',f'r{i}')
e(0xA0,'ORL C,','/b'); e(0xA1,'AJMP','a'); e(0xA2,'MOV C,','b'); e(0xA3,'INC DPTR')
e(0xA4,'MUL AB'); e(0xA5,None); e(0xA6,'MOV','@r0=d'); e(0xA7,'MOV','@r1=d')
for i in range(8): e(0xA8+i,'MOV',f'r{i}=d')
e(0xB0,'ANL C,','/b'); e(0xB1,'ACALL','a'); e(0xB2,'CPL','b'); e(0xB3,'CPL C')
e(0xB4,'CJNE A,','j8'); e(0xB5,'CJNE A,','jd'); e(0xB6,'CJNE','@r0 j'); e(0xB7,'CJNE','@r1 j')
for i in range(8): e(0xB8+i,'CJNE',f'r{i} j')
e(0xC0,'PUSH','d'); e(0xC1,'AJMP','a'); e(0xC2,'CLR','b'); e(0xC3,'CLR C')
e(0xC4,'SWAP A'); e(0xC5,'XCH A,','d'); e(0xC6,'XCH A,','@r0'); e(0xC7,'XCH A,','@r1')
for i in range(8): e(0xC8+i,'XCH A,',f'r{i}')
e(0xD0,'POP','d'); e(0xD1,'ACALL','a'); e(0xD2,'SETB','b'); e(0xD3,'SETB C')
e(0xD4,'DA A'); e(0xD5,'DJNZ','sdj'); e(0xD6,'XCHD A,@r0'); e(0xD7,'XCHD A,@r1')
for i in range(8): e(0xD8+i,'DJNZ',f'r{i} r')
e(0xE0,'MOVX A,@DPTR'); e(0xE1,'AJMP','a'); e(0xE2,'MOVX A,@r0'); e(0xE3,'MOVX A,@r1')
e(0xE4,'CLR A'); e(0xE5,'MOV A,','d'); e(0xE6,'MOV A,','@r0'); e(0xE7,'MOV A,','@r1')
for i in range(8): e(0xE8+i,'MOV A,',f'r{i}')
e(0xF0,'MOVX @DPTR,A'); e(0xF1,'AJMP','a'); e(0xF2,'MOVX @r0,A'); e(0xF3,'MOVX @r1,A')
e(0xF4,'CPL A'); e(0xF5,'MOV','d=A'); e(0xF6,'MOV','@r0=A'); e(0xF7,'MOV','@r1=A')
for i in range(8): e(0xF8+i,'MOV',f'r{i}=A')

SFR = {0xE0:'ACC',0xF0:'B',0x82:'DPL',0x83:'DPH',0x81:'SP',0x80:'P0',0x90:'P1',0xA0:'P2',0xB0:'P3'}

def disasm(code, base, start, length, xdata_names=None):
    xdata_names = xdata_names or {}
    out = []
    pc = start
    end = start + length
    while pc < end:
        off = pc - base
        op = code[off]
        if op not in T:
            out.append(f'{pc:04X}: {op:02X}         db 0x{op:02x}')
            pc += 1
            continue
        m, t = T[op]
        raw = code[off:off+1]
        s = m
        try:
            if t == '':
                out.append(f'{pc:04X}: {raw.hex():<8} {s}')
                pc += 1
            elif t == 'a':
                tgt = ((pc >> 8) & 0xF8) << 8 | ((op >> 5) & 7) << 8 | code[off+1]
                out.append(f'{pc:04X}: {raw.hex():<8} {s} 0x{tgt:04X}')
                pc += 2
            elif t == 'A':
                tgt = (code[off+1] << 8) | code[off+2]
                out.append(f'{pc:04X}: {raw.hex():<8} {s} 0x{tgt:04X}')
                pc += 3
            elif t == 'r':
                rel = code[off+1] if code[off+1] < 128 else code[off+1] - 256
                out.append(f'{pc:04X}: {raw.hex():<8} {s} 0x{pc+2+rel:04X}')
                pc += 2
            elif t == 'i':
                v = code[off+1]
                out.append(f'{pc:04X}: {raw.hex():<8} {s}#0x{v:02x}')
                pc += 2
            elif t == 'i16':
                v = (code[off+1] << 8) | code[off+2]
                nm = xdata_names.get(v, '')
                out.append(f'{pc:04X}: {raw.hex():<8} {s}#0x{v:04x} {nm}')
                pc += 3
            elif t == 'd':
                v = code[off+1]
                out.append(f'{pc:04X}: {raw.hex():<8} {s} {SFR.get(v, hex(v))}')
                pc += 2
            elif t in ('r0=i','r1=i','r2=i','r3=i','r4=i','r5=i','r6=i','r7=i'):
                out.append(f'{pc:04X}: {raw.hex():<8} {s} #0x{code[off+1]:02x}')
                pc += 2
            elif t in ('r0=d','r1=d','r2=d','r3=d','r4=d','r5=d','r6=d','r7=d'):
                out.append(f'{pc:04X}: {raw.hex():<8} {s} {SFR.get(code[off+1],hex(code[off+1]))}')
                pc += 2
            elif t == 'b' or t == '/b':
                v = code[off+1]
                out.append(f'{pc:04X}: {raw.hex():<8} {s} {SFR.get(v, hex(v))}')
                pc += 2
            elif t == 'x':
                d = code[off+1]
                out.append(f'{pc:04X}: {raw.hex():<8} {s} {SFR.get(d,hex(d))},A')
                pc += 2
            elif t == 'x!':
                d, imm = code[off+1], code[off+2]
                out.append(f'{pc:04X}: {raw.hex():<8} {s} {SFR.get(d,hex(d))},#0x{imm:02x}')
                pc += 3
            elif t == 'd=i':
                d, imm = code[off+1], code[off+2]
                out.append(f'{pc:04X}: {raw.hex():<8} {s} {SFR.get(d,hex(d))},#0x{imm:02x}')
                pc += 3
            elif t == '@r0=i' or t == '@r1=i':
                out.append(f'{pc:04X}: {raw.hex():<8} {s} #0x{code[off+1]:02x}')
                pc += 2
            elif t == '@r0' or t == '@r1':
                out.append(f'{pc:04X}: {raw.hex():<8} {s}')
                pc += 1
            elif t in ('r0','r1','r2','r3','r4','r5','r6','r7'):
                out.append(f'{pc:04X}: {raw.hex():<8} {s}')
                pc += 1
            elif t == '@r0=d' or t == '@r1=d':
                out.append(f'{pc:04X}: {raw.hex():<8} {s} {SFR.get(code[off+1],hex(code[off+1]))}')
                pc += 2
            elif t == 'bd':
                out.append(f'{pc:04X}: {raw.hex():<8} {s} (bit,{code[off+1]:02x})')
                pc += 2
            elif t == 'j':
                b, rel = code[off+1], code[off+2]
                if rel >= 128: rel -= 256
                out.append(f'{pc:04X}: {raw.hex():<8} {s} {SFR.get(b,hex(b))}, 0x{pc+3+rel:04X}')
                pc += 3
            elif t == 'j8':
                imm, rel = code[off+1], code[off+2]
                if rel >= 128: rel -= 256
                out.append(f'{pc:04X}: {raw.hex():<8} {s} #0x{imm:02x}, 0x{pc+3+rel:04X}')
                pc += 3
            elif t == 'jd':
                d, rel = code[off+1], code[off+2]
                if rel >= 128: rel -= 256
                out.append(f'{pc:04X}: {raw.hex():<8} {s} {SFR.get(d,hex(d))}, 0x{pc+3+rel:04X}')
                pc += 3
            elif t == '@r0 j' or t == '@r1 j':
                imm, rel = code[off+1], code[off+2]
                if rel >= 128: rel -= 256
                out.append(f'{pc:04X}: {raw.hex():<8} {s} #0x{imm:02x}, 0x{pc+3+rel:04X}')
                pc += 3
            elif t.endswith(' j'):
                imm, rel = code[off+1], code[off+2]
                if rel >= 128: rel -= 256
                out.append(f'{pc:04X}: {raw.hex():<8} {s} #0x{imm:02x}, 0x{pc+3+rel:04X}')
                pc += 3
            elif t == 'd=d':
                s1, s2 = code[off+1], code[off+2]
                out.append(f'{pc:04X}: {raw.hex():<8} {s} {SFR.get(s2,hex(s2))},{SFR.get(s1,hex(s1))}')
                pc += 3
            elif t == 'd=A':
                out.append(f'{pc:04X}: {raw.hex():<8} {s} {SFR.get(code[off+1],hex(code[off+1]))},A')
                pc += 2
            elif t == '@r0=A' or t == '@r1=A':
                out.append(f'{pc:04X}: {raw.hex():<8} {s}')
                pc += 1
            elif t == 'sdj':
                d, rel = code[off+1], code[off+2]
                if rel >= 128: rel -= 256
                out.append(f'{pc:04X}: {raw.hex():<8} {s} {SFR.get(d,hex(d))}, 0x{pc+3+rel:04X}')
                pc += 3
            elif t.endswith(' r'):
                rel = code[off+1]
                if rel >= 128: rel -= 256
                out.append(f'{pc:04X}: {raw.hex():<8} {s} 0x{pc+2+rel:04X}')
                pc += 2
            elif t in ('r0=i','r1=i','r2=i','r3=i','r4=i','r5=i','r6=i','r7=i'):
                out.append(f'{pc:04X}: {raw.hex():<8} {s} #0x{code[off+1]:02x}')
                pc += 2
            elif t in ('r0=d','r1=d','r2=d','r3=d','r4=d','r5=d','r6=d','r7=d'):
                out.append(f'{pc:04X}: {raw.hex():<8} {s} {SFR.get(code[off+1],hex(code[off+1]))}')
                pc += 2
            else:
                out.append(f'{pc:04X}: {raw.hex():<8} {s} ?{t}?')
                pc += 1
        except IndexError:
            out.append(f'{pc:04X}: {raw.hex():<8} (truncado)')
            break
    return '\n'.join(out)

if __name__ == '__main__':
    path = sys.argv[1]
    base_off = int(sys.argv[2], 16)   # offset flash donde empieza el codigo
    base_addr = int(sys.argv[3], 16)  # direccion 8051 de ese offset
    start = int(sys.argv[4], 16)
    length = int(sys.argv[5], 16)
    code = open(path, 'rb').read()
    print(disasm(code, base_off + base_addr, start, length))
