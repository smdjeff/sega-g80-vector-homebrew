   dasm48 -- Intel MCS-48 (8048, 8049) Disassembler --
-----------------------------------------------------------------

;   Processing "5400romset.bin" (27648 bytes)
;   Disassembly start address: 0x0000
;   String terminator: 0x00

___CL_0001:
    0000:    E5             SEL      MB0
    0001:    04 0E          JMP      0000EH
    0003:    15             DIS      I
    0004:    00             NOP      
    0005:    00             NOP      
    0006:    93             RETR     
    0007:    35             DIS      TCNTI
    0008:    00             NOP      
    0009:    00             NOP      
    000A:    93             RETR     
    000B:    02             OUTL     BUS, A
    000C:    05             EN       I
    000D:    61             ADD      A, @R1
    000E:    27             CLR      A
    000F:    3A             OUTL     P2, A
    0010:    15             DIS      I
    0011:    35             DIS      TCNTI
    0012:    65             STOP     TCNT
    0013:    55             STRT     T
    0014:    75             ENT0     CLK
    0015:    E5             SEL      MB0
    0016:    23 10          MOV      A, #010H
    0018:    D7             MOV      PSW, A
    0019:    A5             CLR      F1
    001A:    B5             CPL      F1
    001B:    23 7F          MOV      A, #07FH
    001D:    39             OUTL     P1, A
    001E:    B8 00          MOV      R0, #000H
    0020:    BA 04          MOV      R2, #004H
    0022:    FA             MOV      A, R2
    0023:    07             DEC      A
    0024:    3A             OUTL     P2, A
    0025:    27             CLR      A
    0026:    90             MOVX     @R0, A
    0027:    E8 26          DJNZ     R0, 00026H
    0029:    EA 22          DJNZ     R2, 00022H
    002B:    23 03          MOV      A, #003H
    002D:    3A             OUTL     P2, A
    002E:    23 01          MOV      A, #001H
    0030:    B9 03          MOV      R1, #003H
    0032:    BC 40          MOV      R4, #040H
    0034:    91             MOVX     @R1, A
    0035:    19             INC      R1
    0036:    19             INC      R1
    0037:    19             INC      R1
    0038:    19             INC      R1
    0039:    EC 34          DJNZ     R4, 00034H
    003B:    27             CLR      A
    003C:    3A             OUTL     P2, A
    003D:    B8 03          MOV      R0, #003H
    003F:    B9 03          MOV      R1, #003H
    0041:    23 36          MOV      A, #036H
    0043:    90             MOVX     @R0, A
    0044:    23 76          MOV      A, #076H
    0046:    90             MOVX     @R0, A
    0047:    23 92          MOV      A, #092H
    0049:    90             MOVX     @R0, A
    004A:    F8             MOV      A, R0
    004B:    03 08          ADD      A, #008H
    004D:    A8             MOV      R0, A
    004E:    E9 41          DJNZ     R1, 00041H
    0050:    23 83          MOV      A, #083H
    0052:    3A             OUTL     P2, A
    0053:    23 43          MOV      A, #043H
    0055:    3A             OUTL     P2, A
    0056:    56 5C          JT1      0005CH
    0058:    14 7D          CALL     0007DH
    005A:    04 56          JMP      00056H
    005C:    23 C3          MOV      A, #0C3H
    005E:    3A             OUTL     P2, A
    005F:    23 43          MOV      A, #043H
    0061:    3A             OUTL     P2, A
    0062:    B9 02          MOV      R1, #002H
    0064:    09             IN       A, P1
    0065:    53 7F          ANL      A, #07FH
    0067:    C6 6B          JZ       0006BH
    0069:    14 83          CALL     00083H
    006B:    81             MOVX     A, @R1
    006C:    C6 56          JZ       00056H
    006E:    A9             MOV      R1, A
    006F:    B8 16          MOV      R0, #016H
    0071:    81             MOVX     A, @R1
    0072:    A0             MOV      @R0, A
    0073:    19             INC      R1
    0074:    18             INC      R0
    0075:    81             MOVX     A, @R1
    0076:    A0             MOV      @R0, A
    0077:    19             INC      R1
    0078:    23 40          MOV      A, #040H
    007A:    3A             OUTL     P2, A
    007B:    27             CLR      A
    007C:    93             RETR     
    007D:    09             IN       A, P1
    007E:    53 7F          ANL      A, #07FH
    0080:    96 83          JNZ      00083H
    0082:    83             RET      
    0083:    AA             MOV      R2, A
    0084:    09             IN       A, P1
    0085:    53 7F          ANL      A, #07FH
    0087:    AB             MOV      R3, A
    0088:    DA             XRL      A, R2
    0089:    C6 8E          JZ       0008EH
    008B:    FB             MOV      A, R3
    008C:    04 83          JMP      00083H
    008E:    23 03          MOV      A, #003H
    0090:    3A             OUTL     P2, A
    0091:    23 43          MOV      A, #043H
    0093:    3A             OUTL     P2, A
    0094:    FA             MOV      A, R2
    0095:    6A             ADD      A, R2
    0096:    AB             MOV      R3, A
    0097:    1B             INC      R3
    0098:    54 00          CALL     00200H
    009A:    F2 CD          JB7      000CDH
    009C:    AC             MOV      R4, A
    009D:    FA             MOV      A, R2
    009E:    53 7E          ANL      A, #07EH
    00A0:    C6 CC          JZ       000CCH
    00A2:    E7             RL       A
    00A3:    03 03          ADD      A, #003H
    00A5:    A8             MOV      R0, A
    00A6:    80             MOVX     A, @R0
    00A7:    07             DEC      A
    00A8:    96 C8          JNZ      000C8H
    00AA:    90             MOVX     @R0, A
    00AB:    F9             MOV      A, R1
    00AC:    AA             MOV      R2, A
    00AD:    C8             DEC      R0
    00AE:    B9 02          MOV      R1, #002H
    00B0:    81             MOVX     A, @R1
    00B1:    90             MOVX     @R0, A
    00B2:    F8             MOV      A, R0
    00B3:    07             DEC      A
    00B4:    07             DEC      A
    00B5:    91             MOVX     @R1, A
    00B6:    80             MOVX     A, @R0
    00B7:    03 03          ADD      A, #003H
    00B9:    A9             MOV      R1, A
    00BA:    C8             DEC      R0
    00BB:    F8             MOV      A, R0
    00BC:    07             DEC      A
    00BD:    91             MOVX     @R1, A
    00BE:    FA             MOV      A, R2
    00BF:    A9             MOV      R1, A
    00C0:    FC             MOV      A, R4
    00C1:    90             MOVX     @R0, A
    00C2:    FB             MOV      A, R3
    00C3:    54 00          CALL     00200H
    00C5:    C8             DEC      R0
    00C6:    90             MOVX     @R0, A
    00C7:    83             RET      
    00C8:    C8             DEC      R0
    00C9:    C8             DEC      R0
    00CA:    04 C0          JMP      000C0H
    00CC:    FC             MOV      A, R4
    00CD:    14 CF          CALL     000CFH
    00CF:    B8 0B          MOV      R0, #00BH
    00D1:    53 7F          ANL      A, #07FH
    00D3:    A0             MOV      @R0, A
    00D4:    FB             MOV      A, R3
    00D5:    54 00          CALL     00200H
    00D7:    C8             DEC      R0
    00D8:    A0             MOV      @R0, A
    00D9:    23 40          MOV      A, #040H
    00DB:    3A             OUTL     P2, A
    00DC:    27             CLR      A
    00DD:    93             RETR     
    00DE:    F8             MOV      A, R0
    00DF:    D5             SEL      RB1
    00E0:    A8             MOV      R0, A
    00E1:    14 F6          CALL     000F6H
    00E3:    23 40          MOV      A, #040H
    00E5:    3A             OUTL     P2, A
    00E6:    93             RETR     
    00E7:    D5             SEL      RB1
    00E8:    C7             MOV      A, PSW
    00E9:    07             DEC      A
    00EA:    53 07          ANL      A, #007H
    00EC:    E7             RL       A
    00ED:    03 08          ADD      A, #008H
    00EF:    A8             MOV      R0, A
    00F0:    14 F6          CALL     000F6H
    00F2:    23 40          MOV      A, #040H
    00F4:    3A             OUTL     P2, A
    00F5:    93             RETR     
    00F6:    23 43          MOV      A, #043H
    00F8:    3A             OUTL     P2, A
    00F9:    F0             MOV      A, @R0
    00FA:    C9             DEC      R1
    00FB:    C9             DEC      R1
    00FC:    91             MOVX     @R1, A
    00FD:    19             INC      R1
    00FE:    18             INC      R0
    00FF:    F0             MOV      A, @R0
    0100:    53 0F          ANL      A, #00FH
    0102:    91             MOVX     @R1, A
    0103:    19             INC      R1
    0104:    83             RET      
    0105:    23 10          MOV      A, #010H
    0107:    D7             MOV      PSW, A
    0108:    23 43          MOV      A, #043H
    010A:    3A             OUTL     P2, A
    010B:    04 64          JMP      00064H
    010D:    23 10          MOV      A, #010H
    010F:    D7             MOV      PSW, A
    0110:    23 43          MOV      A, #043H
    0112:    3A             OUTL     P2, A
    0113:    19             INC      R1
    0114:    81             MOVX     A, @R1
    0115:    A8             MOV      R0, A
    0116:    18             INC      R0
    0117:    18             INC      R0
    0118:    C9             DEC      R1
    0119:    81             MOVX     A, @R1
    011A:    90             MOVX     @R0, A
    011B:    03 03          ADD      A, #003H
    011D:    A8             MOV      R0, A
    011E:    19             INC      R1
    011F:    81             MOVX     A, @R1
    0120:    90             MOVX     @R0, A
    0121:    23 01          MOV      A, #001H
    0123:    91             MOVX     @R1, A
    0124:    C9             DEC      R1
    0125:    04 64          JMP      00064H
    0127:    23 43          MOV      A, #043H
    0129:    3A             OUTL     P2, A
    012A:    93             RETR     
    012B:    D5             SEL      RB1
    012C:    C7             MOV      A, PSW
    012D:    07             DEC      A
    012E:    53 07          ANL      A, #007H
    0130:    E7             RL       A
    0131:    03 08          ADD      A, #008H
    0133:    A8             MOV      R0, A
    0134:    14 F6          CALL     000F6H
    0136:    23 10          MOV      A, #010H
    0138:    D7             MOV      PSW, A
    0139:    04 64          JMP      00064H
    013B:    D5             SEL      RB1
    013C:    42             MOV      A, T
    013D:    6F             ADD      A, R7
    013E:    AA             MOV      R2, A
    013F:    A8             MOV      R0, A
    0140:    6A             ADD      A, R2
    0141:    AA             MOV      R2, A
    0142:    6A             ADD      A, R2
    0143:    AA             MOV      R2, A
    0144:    6A             ADD      A, R2
    0145:    6A             ADD      A, R2
    0146:    68             ADD      A, R0
    0147:    17             INC      A
    0148:    AF             MOV      R7, A
    0149:    C5             SEL      RB0
    014A:    AA             MOV      R2, A
    014B:    FB             MOV      A, R3
    014C:    C6 56          JZ       00056H
    014E:    37             CPL      A
    014F:    17             INC      A
    0150:    A8             MOV      R0, A
    0151:    FA             MOV      A, R2
    0152:    AA             MOV      R2, A
    0153:    68             ADD      A, R0
    0154:    F6 52          JC       00052H
    0156:    93             RETR     
    0157:    41             ORL      A, @R1
    0158:    0D             MOVD     A, P5
    0159:    09             IN       A, P1
    015A:    53 B8          ANL      A, #0B8H
    015C:    1F             INC      R7
    015D:    BA 00          MOV      R2, #000H
    015F:    F4 99          CALL     00799H
    0161:    34 FC          CALL     001FCH
    0163:    B8 20          MOV      R0, #020H
    0165:    BD 04          MOV      R5, #004H
    0167:    BE 01          MOV      R6, #001H
    0169:    76 79          JF1      00079H
    016B:    B8 23          MOV      R0, #023H
    016D:    BA 02          MOV      R2, #002H
    016F:    F4 99          CALL     00799H
    0171:    34 FC          CALL     001FCH
    0173:    B8 24          MOV      R0, #024H
    0175:    BD 03          MOV      R5, #003H
    0177:    BE 3A          MOV      R6, #03AH
    0179:    27             CLR      A
    017A:    AB             MOV      R3, A
    017B:    AC             MOV      R4, A
    017C:    AF             MOV      R7, A
    017D:    B9 1C          MOV      R1, #01CH
    017F:    F4 AC          CALL     007ACH
    0181:    E6 8A          JNC      0008AH
    0183:    1B             INC      R3
    0184:    C6 8A          JZ       0008AH
    0186:    FD             MOV      A, R5
    0187:    91             MOVX     @R1, A
    0188:    F4 00          CALL     00700H
    018A:    B9 1D          MOV      R1, #01DH
    018C:    F4 AC          CALL     007ACH
    018E:    E6 97          JNC      00097H
    0190:    1C             INC      R4
    0191:    C6 97          JZ       00097H
    0193:    FD             MOV      A, R5
    0194:    91             MOVX     @R1, A
    0195:    F4 0C          CALL     0070CH
    0197:    B9 1E          MOV      R1, #01EH
    0199:    F4 AC          CALL     007ACH
    019B:    E6 A4          JNC      000A4H
    019D:    1F             INC      R7
    019E:    C6 A4          JZ       000A4H
    01A0:    FD             MOV      A, R5
    01A1:    91             MOVX     @R1, A
    01A2:    F4 18          CALL     00718H
    01A4:    F4 25          CALL     00725H
    01A6:    F6 C3          JC       000C3H
    01A8:    B6 C1          JF0      000C1H
    01AA:    FE             MOV      A, R6
    01AB:    B4 12          CALL     00512H
    01AD:    AE             MOV      R6, A
    01AE:    B9 14          MOV      R1, #014H
    01B0:    FB             MOV      A, R3
    01B1:    C6 B5          JZ       000B5H
    01B3:    FE             MOV      A, R6
    01B4:    91             MOVX     @R1, A
    01B5:    19             INC      R1
    01B6:    FC             MOV      A, R4
    01B7:    C6 BB          JZ       000BBH
    01B9:    FE             MOV      A, R6
    01BA:    91             MOVX     @R1, A
    01BB:    19             INC      R1
    01BC:    FF             MOV      A, R7
    01BD:    C6 C1          JZ       000C1H
    01BF:    FE             MOV      A, R6
    01C0:    91             MOVX     @R1, A
    01C1:    24 F4          JMP      001F4H
    01C3:    B9 1C          MOV      R1, #01CH
    01C5:    B8 14          MOV      R0, #014H
    01C7:    FB             MOV      A, R3
    01C8:    C6 CD          JZ       000CDH
    01CA:    27             CLR      A
    01CB:    91             MOVX     @R1, A
    01CC:    90             MOVX     @R0, A
    01CD:    18             INC      R0
    01CE:    19             INC      R1
    01CF:    FC             MOV      A, R4
    01D0:    C6 D5          JZ       000D5H
    01D2:    27             CLR      A
    01D3:    91             MOVX     @R1, A
    01D4:    90             MOVX     @R0, A
    01D5:    18             INC      R0
    01D6:    19             INC      R1
    01D7:    FF             MOV      A, R7
    01D8:    C6 DD          JZ       000DDH
    01DA:    27             CLR      A
    01DB:    91             MOVX     @R1, A
    01DC:    90             MOVX     @R0, A
    01DD:    24 F8          JMP      001F8H
    01DF:    43 4F          ORL      A, #04FH
    01E1:    44 45          JMP      00245H
    01E3:    3A             OUTL     P2, A
    01E4:    0D             MOVD     A, P5
    01E5:    0D             MOVD     A, P5
    01E6:    3B             ???      
    01E7:    2A             XCH      A, R2
    01E8:    2A             XCH      A, R2
    01E9:    2A             XCH      A, R2
    01EA:    2A             XCH      A, R2
    01EB:    2A             XCH      A, R2
    01EC:    2A             XCH      A, R2
    01ED:    2A             XCH      A, R2
    01EE:    2A             XCH      A, R2
    01EF:    2A             XCH      A, R2
    01F0:    04 DE          JMP      000DEH
    01F2:    04 00          JMP      ___CL_0001
    01F4:    24 05          JMP      00105H
    01F6:    24 2B          JMP      0012BH
    01F8:    24 0D          JMP      0010DH
    01FA:    24 27          JMP      00127H
    01FC:    04 E7          JMP      000E7H
    01FE:    4E             ORL      A, R6
    01FF:    54 A3          CALL     002A3H
    0201:    83             RET      
    0202:    81             MOVX     A, @R1
    0203:    FA             MOV      A, R2
    0204:    81             MOVX     A, @R1
    0205:    FA             MOV      A, R2
    0206:    81             MOVX     A, @R1
    0207:    FA             MOV      A, R2
    0208:    0B             ???      
    0209:    00             NOP      
    020A:    0B             ???      
    020B:    14 0C          CALL     0000CH
    020D:    19             INC      R1
    020E:    0C             MOVD     A, P4
    020F:    00             NOP      
    0210:    06             ???      
    0211:    12 81          JB0      00081H
    0213:    FA             MOV      A, R2
    0214:    08             INS      A, BUS
    0215:    00             NOP      
    0216:    81             MOVX     A, @R1
    0217:    FA             MOV      A, R2
    0218:    09             IN       A, P1
    0219:    00             NOP      
    021A:    09             IN       A, P1
    021B:    34 09          CALL     00109H
    021D:    3D             MOVD     P5, A
    021E:    81             MOVX     A, @R1
    021F:    FA             MOV      A, R2
    0220:    02             OUTL     BUS, A
    0221:    6C             ADD      A, R4
    0222:    02             OUTL     BUS, A
    0223:    60             ADD      A, @R0
    0224:    02             OUTL     BUS, A
    0225:    A9             MOV      R1, A
    0226:    81             MOVX     A, @R1
    0227:    FA             MOV      A, R2
    0228:    01             ???      
    0229:    5B             ANL      A, R3
    022A:    81             MOVX     A, @R1
    022B:    FA             MOV      A, R2
    022C:    0A             IN       A, P2
    022D:    10             INC      @R0
    022E:    81             MOVX     A, @R1
    022F:    FA             MOV      A, R2
    0230:    0D             MOVD     A, P5
    0231:    70             ADDC     A, @R0
    0232:    0D             MOVD     A, P5
    0233:    76 0A          JF1      0000AH
    0235:    08             INS      A, BUS
    0236:    81             MOVX     A, @R1
    0237:    FA             MOV      A, R2
    0238:    0D             MOVD     A, P5
    0239:    00             NOP      
    023A:    81             MOVX     A, @R1
    023B:    FA             MOV      A, R2
    023C:    01             ???      
    023D:    6B             ADD      A, R3
    023E:    81             MOVX     A, @R1
    023F:    FA             MOV      A, R2
    0240:    0E             MOVD     A, P6
    0241:    4A             ORL      A, R2
    0242:    8E             ORLD     P6, A
    0243:    08             INS      A, BUS
    0244:    0A             IN       A, P2
    0245:    00             NOP      
    0246:    81             MOVX     A, @R1
    0247:    FA             MOV      A, R2
    0248:    02             OUTL     BUS, A
    0249:    64 02          JMP      00302H
    024B:    68             ADD      A, R0
    024C:    09             IN       A, P1
    024D:    86 09          JNI      00009H
    024F:    8C             ORLD     P4, A
    0250:    09             IN       A, P1
    0251:    92 08          JB4      00008H
    0253:    A1             MOV      @R1, A
    0254:    09             IN       A, P1
    0255:    00             NOP      
    0256:    09             IN       A, P1
    0257:    02             OUTL     BUS, A
    0258:    0E             MOVD     A, P6
    0259:    14 0E          CALL     0000EH
    025B:    1A             INC      R2
    025C:    0E             MOVD     A, P6
    025D:    63             ???      
    025E:    8D             ORLD     P5, A
    025F:    64 BA          JMP      003BAH
    0261:    46 76          JNT1     00076H
    0263:    6E             ADD      A, R6
    0264:    BA 3E          MOV      R2, #03EH
    0266:    76 6E          JF1      0006EH
    0268:    BA 42          MOV      R2, #042H
    026A:    76 6E          JF1      0006EH
    026C:    BA 3A          MOV      R2, #03AH
    026E:    B9 19          MOV      R1, #019H
    0270:    23 06          MOV      A, #006H
    0272:    91             MOVX     @R1, A
    0273:    B8 27          MOV      R0, #027H
    0275:    F4 99          CALL     00799H
    0277:    F4 99          CALL     00799H
    0279:    34 FC          CALL     001FCH
    027B:    B8 28          MOV      R0, #028H
    027D:    F4 5D          CALL     0075DH
    027F:    F6 A0          JC       000A0H
    0281:    B6 8B          JF0      0008BH
    0283:    FE             MOV      A, R6
    0284:    F2 A0          JB7      000A0H
    0286:    B4 12          CALL     00512H
    0288:    B9 0C          MOV      R1, #00CH
    028A:    91             MOVX     @R1, A
    028B:    B8 2C          MOV      R0, #02CH
    028D:    F4 5D          CALL     0075DH
    028F:    B6 9E          JF0      0009EH
    0291:    B8 08          MOV      R0, #008H
    0293:    FE             MOV      A, R6
    0294:    6E             ADD      A, R6
    0295:    AE             MOV      R6, A
    0296:    17             INC      A
    0297:    B4 10          CALL     00510H
    0299:    90             MOVX     @R0, A
    029A:    FE             MOV      A, R6
    029B:    B4 10          CALL     00510H
    029D:    90             MOVX     @R0, A
    029E:    24 F4          JMP      001F4H
    02A0:    27             CLR      A
    02A1:    B9 19          MOV      R1, #019H
    02A3:    91             MOVX     @R1, A
    02A4:    B9 0C          MOV      R1, #00CH
    02A6:    91             MOVX     @R1, A
    02A7:    24 F8          JMP      001F8H
    02A9:    B9 1D          MOV      R1, #01DH
    02AB:    23 0A          MOV      A, #00AH
    02AD:    91             MOVX     @R1, A
    02AE:    B8 20          MOV      R0, #020H
    02B0:    B0 FF          MOV      @R0, #0FFH
    02B2:    18             INC      R0
    02B3:    B0 FF          MOV      @R0, #0FFH
    02B5:    B8 2F          MOV      R0, #02FH
    02B7:    BA 4A          MOV      R2, #04AH
    02B9:    F4 99          CALL     00799H
    02BB:    F4 99          CALL     00799H
    02BD:    34 FC          CALL     001FCH
    02BF:    B8 30          MOV      R0, #030H
    02C1:    F4 25          CALL     00725H
    02C3:    F6 EE          JC       000EEH
    02C5:    B8 20          MOV      R0, #020H
    02C7:    B6 D3          JF0      000D3H
    02C9:    FE             MOV      A, R6
    02CA:    B4 12          CALL     00512H
    02CC:    B9 15          MOV      R1, #015H
    02CE:    91             MOVX     @R1, A
    02CF:    F0             MOV      A, @R0
    02D0:    03 FA          ADD      A, #0FAH
    02D2:    A0             MOV      @R0, A
    02D3:    F0             MOV      A, @R0
    02D4:    18             INC      R0
    02D5:    60             ADD      A, @R0
    02D6:    A0             MOV      @R0, A
    02D7:    E6 EC          JNC      000ECH
    02D9:    B8 34          MOV      R0, #034H
    02DB:    F4 25          CALL     00725H
    02DD:    B6 EC          JF0      000ECH
    02DF:    B8 11          MOV      R0, #011H
    02E1:    FE             MOV      A, R6
    02E2:    6E             ADD      A, R6
    02E3:    AE             MOV      R6, A
    02E4:    17             INC      A
    02E5:    B4 10          CALL     00510H
    02E7:    90             MOVX     @R0, A
    02E8:    FE             MOV      A, R6
    02E9:    B4 10          CALL     00510H
    02EB:    90             MOVX     @R0, A
    02EC:    24 F4          JMP      001F4H
    02EE:    27             CLR      A
    02EF:    B9 15          MOV      R1, #015H
    02F1:    91             MOVX     @R1, A
    02F2:    B9 1D          MOV      R1, #01DH
    02F4:    91             MOVX     @R1, A
    02F5:    24 F8          JMP      001F8H
    02F7:    8C             ORLD     P4, A
    02F8:    C8             DEC      R0
    02F9:    8C             ORLD     P4, A
    02FA:    C8             DEC      R0
    02FB:    8C             ORLD     P4, A
    02FC:    C8             DEC      R0
    02FD:    8C             ORLD     P4, A
    02FE:    8F             ORLD     P7, A
    02FF:    80             MOVX     A, @R0
    0300:    00             NOP      
    0301:    01             ???      
    0302:    A0             MOV      @R0, A
    0303:    00             NOP      
    0304:    0F             MOVD     A, P7
    0305:    12 FF          JB0      000FFH
    0307:    00             NOP      
    0308:    00             NOP      
    0309:    0B             ???      
    030A:    01             ???      
    030B:    01             ???      
    030C:    03 0A          ADD      A, #00AH
    030E:    FF             MOV      A, R7
    030F:    08             INS      A, BUS
    0310:    1E             INC      R6
    0311:    FF             MOV      A, R7
    0312:    00             NOP      
    0313:    00             NOP      
    0314:    00             NOP      
    0315:    02             OUTL     BUS, A
    0316:    0A             IN       A, P2
    0317:    01             ???      
    0318:    01             ???      
    0319:    0A             IN       A, P2
    031A:    00             NOP      
    031B:    02             OUTL     BUS, A
    031C:    0A             IN       A, P2
    031D:    FF             MOV      A, R7
    031E:    01             ???      
    031F:    64 00          JMP      00300H
    0321:    0D             MOVD     A, P5
    0322:    08             INS      A, BUS
    0323:    FF             MOV      A, R7
    0324:    00             NOP      
    0325:    00             NOP      
    0326:    1B             INC      R3
    0327:    01             ???      
    0328:    FD             MOV      A, R5
    0329:    01             ???      
    032A:    01             ???      
    032B:    51             ANL      A, @R1
    032C:    00             NOP      
    032D:    26 00          JNT0     ___CL_0001
    032F:    0C             MOVD     A, P4
    0330:    02             OUTL     BUS, A
    0331:    01             ???      
    0332:    09             IN       A, P1
    0333:    0F             MOVD     A, P7
    0334:    FF             MOV      A, R7
    0335:    00             NOP      
    0336:    00             NOP      
    0337:    00             NOP      
    0338:    01             ???      
    0339:    78             ADDC     A, R0
    033A:    00             NOP      
    033B:    0B             ???      
    033C:    05             EN       I
    033D:    FF             MOV      A, R7
    033E:    01             ???      
    033F:    39             OUTL     P1, A
    0340:    00             NOP      
    0341:    0C             MOVD     A, P4
    0342:    02             OUTL     BUS, A
    0343:    01             ???      
    0344:    01             ???      
    0345:    98 00          ANL      BUS, #000H
    0347:    07             DEC      A
    0348:    0A             IN       A, P2
    0349:    FF             MOV      A, R7
    034A:    00             NOP      
    034B:    00             NOP      
    034C:    01             ???      
    034D:    E8 7F          DJNZ     R0, 0007FH
    034F:    01             ???      
    0350:    50             ANL      A, @R0
    0351:    00             NOP      
    0352:    3C             MOVD     P4, A
    0353:    03 01          ADD      A, #001H
    0355:    FF             MOV      A, R7
    0356:    FF             MOV      A, R7
    0357:    00             NOP      
    0358:    01             ???      
    0359:    70             ADDC     A, @R0
    035A:    00             NOP      
    035B:    0B             ???      
    035C:    0A             IN       A, P2
    035D:    FF             MOV      A, R7
    035E:    02             OUTL     BUS, A
    035F:    64 FF          JMP      003FFH
    0361:    00             NOP      
    0362:    55             STRT     T
    0363:    00             NOP      
    0364:    01             ???      
    0365:    14 00          CALL     ___CL_0001
    0367:    04 03          JMP      00003H
    0369:    FF             MOV      A, R7
    036A:    04 06          JMP      00006H
    036C:    01             ???      
    036D:    0F             MOVD     A, P7
    036E:    1E             INC      R6
    036F:    FF             MOV      A, R7
    0370:    00             NOP      
    0371:    00             NOP      
    0372:    01             ???      
    0373:    06             ???      
    0374:    38             ???      
    0375:    00             NOP      
    0376:    86 00          JNI      ___CL_0001
    0378:    01             ???      
    0379:    64 00          JMP      00300H
    037B:    0F             MOVD     A, P7
    037C:    3C             MOVD     P4, A
    037D:    FF             MOV      A, R7
    037E:    00             NOP      
    037F:    00             NOP      
    0380:    05             EN       I
    0381:    05             EN       I
    0382:    01             ???      
    0383:    08             INS      A, BUS
    0384:    1E             INC      R6
    0385:    FF             MOV      A, R7
    0386:    FF             MOV      A, R7
    0387:    FF             MOV      A, R7
    0388:    00             NOP      
    0389:    08             INS      A, BUS
    038A:    04 FF          JMP      000FFH
    038C:    01             ???      
    038D:    01             ???      
    038E:    08             INS      A, BUS
    038F:    00             NOP      
    0390:    89 00          ORL      P1, #000H
    0392:    09             IN       A, P1
    0393:    02             OUTL     BUS, A
    0394:    01             ???      
    0395:    09             IN       A, P1
    0396:    02             OUTL     BUS, A
    0397:    FF             MOV      A, R7
    0398:    00             NOP      
    0399:    92 00          JB4      ___CL_0001
    039B:    08             INS      A, BUS
    039C:    2F             XCH      A, R7
    039D:    01             ???      
    039E:    00             NOP      
    039F:    B4 00          CALL     00500H
    03A1:    2F             XCH      A, R7
    03A2:    08             INS      A, BUS
    03A3:    01             ???      
    03A4:    00             NOP      
    03A5:    B4 00          CALL     00500H
    03A7:    DC             XRL      A, R4
    03A8:    02             OUTL     BUS, A
    03A9:    01             ???      
    03AA:    00             NOP      
    03AB:    00             NOP      
    03AC:    FF             MOV      A, R7
    03AD:    02             OUTL     BUS, A
    03AE:    FF             MOV      A, R7
    03AF:    00             NOP      
    03B0:    00             NOP      
    03B1:    2D             XCH      A, R5
    03B2:    08             INS      A, BUS
    03B3:    FF             MOV      A, R7
    03B4:    FF             MOV      A, R7
    03B5:    FF             MOV      A, R7
    03B6:    00             NOP      
    03B7:    08             INS      A, BUS
    03B8:    2D             XCH      A, R5
    03B9:    FF             MOV      A, R7
    03BA:    00             NOP      
    03BB:    B4 00          CALL     00500H
    03BD:    0F             MOVD     A, P7
    03BE:    0F             MOVD     A, P7
    03BF:    FF             MOV      A, R7
    03C0:    00             NOP      
    03C1:    00             NOP      
    03C2:    06             ???      
    03C3:    15             DIS      I
    03C4:    01             ???      
    03C5:    01             ???      
    03C6:    A3             MOVP     A, @A
    03C7:    05             EN       I
    03C8:    01             ???      
    03C9:    64 FE          JMP      003FEH
    03CB:    01             ???      
    03CC:    C8             DEC      R0
    03CD:    FF             MOV      A, R7
    03CE:    00             NOP      
    03CF:    00             NOP      
    03D0:    02             OUTL     BUS, A
    03D1:    91             MOVX     @R1, A
    03D2:    00             NOP      
    03D3:    01             ???      
    03D4:    01             ???      
    03D5:    38             ???      
    03D6:    21             XCH      A, @R1
    03D7:    03 FF          ADD      A, #0FFH
    03D9:    30             XCHD     A, @R0
    03DA:    01             ???      
    03DB:    01             ???      
    03DC:    49             ORL      A, R1
    03DD:    02             OUTL     BUS, A
    03DE:    FF             MOV      A, R7
    03DF:    00             NOP      
    03E0:    F1             MOV      A, @R1
    03E1:    00             NOP      
    03E2:    0D             MOVD     A, P5
    03E3:    0A             IN       A, P2
    03E4:    01             ???      
    03E5:    01             ???      
    03E6:    6A             ADD      A, R2
    03E7:    FD             MOV      A, R5
    03E8:    04 51          JMP      00051H
    03EA:    FF             MOV      A, R7
    03EB:    00             NOP      
    03EC:    F1             MOV      A, @R1
    03ED:    00             NOP      
    03EE:    04 21          JMP      00021H
    03F0:    01             ???      
    03F1:    FF             MOV      A, R7
    03F2:    FF             MOV      A, R7
    03F3:    00             NOP      
    03F4:    48             ORL      A, R0
    03F5:    04 FF          JMP      000FFH
    03F7:    01             ???      
    03F8:    01             ???      
    03F9:    48             ORL      A, R0
    03FA:    00             NOP      
    03FB:    F1             MOV      A, @R1
    03FC:    C8             DEC      R0
    03FD:    8C             ORLD     P4, A
    03FE:    C8             DEC      R0
    03FF:    8C             ORLD     P4, A
    0400:    FF             MOV      A, R7
    0401:    0F             MOVD     A, P7
    0402:    07             DEC      A
    0403:    00             NOP      
    0404:    00             NOP      
    0405:    0D             MOVD     A, P5
    0406:    01             ???      
    0407:    01             ???      
    0408:    03 01          ADD      A, #001H
    040A:    FF             MOV      A, R7
    040B:    01             ???      
    040C:    78             ADDC     A, R0
    040D:    00             NOP      
    040E:    0A             IN       A, P2
    040F:    05             EN       I
    0410:    FF             MOV      A, R7
    0411:    00             NOP      
    0412:    00             NOP      
    0413:    24 05          JMP      00105H
    0415:    01             ???      
    0416:    FF             MOV      A, R7
    0417:    FF             MOV      A, R7
    0418:    00             NOP      
    0419:    0B             ???      
    041A:    32 FF          JB1      000FFH
    041C:    00             NOP      
    041D:    00             NOP      
    041E:    14 03          CALL     00003H
    0420:    01             ???      
    0421:    01             ???      
    0422:    01             ???      
    0423:    EC 00          DJNZ     R4, ___CL_0001
    0425:    1E             INC      R6
    0426:    00             NOP      
    0427:    0A             IN       A, P2
    0428:    01             ???      
    0429:    01             ???      
    042A:    0A             IN       A, P2
    042B:    65             STOP     TCNT
    042C:    FF             MOV      A, R7
    042D:    00             NOP      
    042E:    00             NOP      
    042F:    32 02          JB1      00002H
    0431:    01             ???      
    0432:    32 02          JB1      00002H
    0434:    FF             MOV      A, R7
    0435:    01             ???      
    0436:    01             ???      
    0437:    32 00          JB1      ___CL_0001
    0439:    32 03          JB1      00003H
    043B:    00             NOP      
    043C:    11             INC      @R1
    043D:    30             XCHD     A, @R0
    043E:    17             INC      A
    043F:    09             IN       A, P1
    0440:    1C             INC      R4
    0441:    3C             MOVD     P4, A
    0442:    17             INC      A
    0443:    0B             ???      
    0444:    1C             INC      R4
    0445:    52 25          JB2      00025H
    0447:    00             NOP      
    0448:    2D             XCH      A, R5
    0449:    34 13          CALL     00113H
    044B:    0D             MOVD     A, P5
    044C:    24 77          JMP      00177H
    044E:    A3             MOVP     A, @A
    044F:    83             RET      
    0450:    2D             XCH      A, R5
    0451:    00             NOP      
    0452:    36 0B          JT0      0000BH
    0454:    4A             ORL      A, R2
    0455:    81             MOVX     A, @R1
    0456:    56 0D          JT1      0000DH
    0458:    00             NOP      
    0459:    0A             IN       A, P2
    045A:    02             OUTL     BUS, A
    045B:    01             ???      
    045C:    02             OUTL     BUS, A
    045D:    96 00          JNZ      ___CL_0001
    045F:    05             EN       I
    0460:    02             OUTL     BUS, A
    0461:    FF             MOV      A, R7
    0462:    07             DEC      A
    0463:    02             OUTL     BUS, A
    0464:    01             ???      
    0465:    05             EN       I
    0466:    A6             ???      
    0467:    00             NOP      
    0468:    0D             MOVD     A, P5
    0469:    05             EN       I
    046A:    FF             MOV      A, R7
    046B:    00             NOP      
    046C:    00             NOP      
    046D:    14 01          CALL     00001H
    046F:    06             ???      
    0470:    02             OUTL     BUS, A
    0471:    96 00          JNZ      ___CL_0001
    0473:    32 01          JB1      00001H
    0475:    FC             MOV      A, R4
    0476:    07             DEC      A
    0477:    64 00          JMP      00300H
    0479:    32 01          JB1      00001H
    047B:    04 FF          JMP      000FFH
    047D:    FF             MOV      A, R7
    047E:    00             NOP      
    047F:    57             DA       A
    0480:    00             NOP      
    0481:    6B             ADD      A, R3
    0482:    50             ANL      A, @R0
    0483:    00             NOP      
    0484:    02             OUTL     BUS, A
    0485:    C8             DEC      R0
    0486:    00             NOP      
    0487:    0A             IN       A, P2
    0488:    1E             INC      R6
    0489:    FF             MOV      A, R7
    048A:    00             NOP      
    048B:    00             NOP      
    048C:    02             OUTL     BUS, A
    048D:    C8             DEC      R0
    048E:    00             NOP      
    048F:    0A             IN       A, P2
    0490:    0A             IN       A, P2
    0491:    FF             MOV      A, R7
    0492:    00             NOP      
    0493:    00             NOP      
    0494:    03 E1          ADD      A, #0E1H
    0496:    00             NOP      
    0497:    0A             IN       A, P2
    0498:    2D             XCH      A, R5
    0499:    FF             MOV      A, R7
    049A:    00             NOP      
    049B:    00             NOP      
    049C:    82             ???      
    049D:    0A             IN       A, P2
    049E:    8A 0A          ORL      P2, #00AH
    04A0:    92 0A          JB4      0000AH
    04A2:    62             MOV      T, A
    04A3:    0F             MOVD     A, P7
    04A4:    70             ADDC     A, @R0
    04A5:    01             ???      
    04A6:    76 0F          JF1      0000FH
    04A8:    7E             ADDC     A, R6
    04A9:    37             CPL      A
    04AA:    6B             ADD      A, R3
    04AB:    0F             MOVD     A, P7
    04AC:    87             ???      
    04AD:    3F             MOVD     P7, A
    04AE:    90             MOVX     @R0, A
    04AF:    00             NOP      
    04B0:    99 00          ANL      P1, #000H
    04B2:    9F             ANLD     P7, A
    04B3:    02             OUTL     BUS, A
    04B4:    A5             CLR      F1
    04B5:    1E             INC      R6
    04B6:    B5             CPL      F1
    04B7:    00             NOP      
    04B8:    AF             MOV      R7, A
    04B9:    02             OUTL     BUS, A
    04BA:    AA             MOV      R2, A
    04BB:    1E             INC      R6
    04BC:    C0             ???      
    04BD:    01             ???      
    04BE:    CE             DEC      R6
    04BF:    16 E0          JTF      000E0H
    04C1:    01             ???      
    04C2:    F2 50          JB7      00050H
    04C4:    EC 01          DJNZ     R4, 00001H
    04C6:    EF 12          DJNZ     R7, 00012H
    04C8:    00             NOP      
    04C9:    0A             IN       A, P2
    04CA:    01             ???      
    04CB:    01             ???      
    04CC:    0F             MOVD     A, P7
    04CD:    0A             IN       A, P2
    04CE:    FF             MOV      A, R7
    04CF:    00             NOP      
    04D0:    00             NOP      
    04D1:    02             OUTL     BUS, A
    04D2:    01             ???      
    04D3:    0B             ???      
    04D4:    02             OUTL     BUS, A
    04D5:    01             ???      
    04D6:    F6 00          JC       ___CL_0001
    04D8:    D1             XRL      A, @R1
    04D9:    00             NOP      
    04DA:    01             ???      
    04DB:    02             OUTL     BUS, A
    04DC:    01             ???      
    04DD:    02             OUTL     BUS, A
    04DE:    01             ???      
    04DF:    02             OUTL     BUS, A
    04E0:    01             ???      
    04E1:    02             OUTL     BUS, A
    04E2:    01             ???      
    04E3:    02             OUTL     BUS, A
    04E4:    02             OUTL     BUS, A
    04E5:    FF             MOV      A, R7
    04E6:    04 01          JMP      00001H
    04E8:    FF             MOV      A, R7
    04E9:    00             NOP      
    04EA:    DA             XRL      A, R2
    04EB:    00             NOP      
    04EC:    0C             MOVD     A, P4
    04ED:    01             ???      
    04EE:    01             ???      
    04EF:    01             ???      
    04F0:    02             OUTL     BUS, A
    04F1:    F4 00          CALL     00700H
    04F3:    EC C7          DJNZ     R4, 000C7H
    04F5:    05             EN       I
    04F6:    CF             DEC      R7
    04F7:    14 C7          CALL     000C7H
    04F9:    00             NOP      
    04FA:    CF             DEC      R7
    04FB:    10             INC      @R0
    04FC:    C8             DEC      R0
    04FD:    8C             ORLD     P4, A
    04FE:    C8             DEC      R0
    04FF:    8C             ORLD     P4, A
    0500:    00             NOP      
    0501:    07             DEC      A
    0502:    0B             ???      
    0503:    10             INC      @R0
    0504:    16 1D          JTF      0001DH
    0506:    26 30          JNT0     00030H
    0508:    3B             ???      
    0509:    48             ORL      A, R0
    050A:    58             ANL      A, R0
    050B:    6B             ADD      A, R3
    050C:    81             MOVX     A, @R1
    050D:    A0             MOV      @R0, A
    050E:    C5             SEL      RB0
    050F:    FF             MOV      A, R7
    0510:    03 10          ADD      A, #010H
    0512:    A3             MOVP     A, @A
    0513:    83             RET      
    0514:    FD             MOV      A, R5
    0515:    18             INC      R0
    0516:    EE E3          DJNZ     R6, 000E3H
    0518:    E1             ???      
    0519:    7B             ADDC     A, R3
    051A:    D4 D4          CALL     006D4H
    051C:    C8             DEC      R0
    051D:    E3             MOVP3    A, @A
    051E:    BD 9B          MOV      R5, #09BH
    0520:    B2 F7          JB5      000F7H
    0522:    A8             MOV      R0, A
    0523:    EB 9F          DJNZ     R3, 0009FH
    0525:    70             ADDC     A, @R0
    0526:    96 7D          JNZ      0007DH
    0528:    8E             ORLD     P6, A
    0529:    0C             MOVD     A, P4
    052A:    86 13          JNI      00013H
    052C:    7E             ADDC     A, R6
    052D:    8C             ORLD     P4, A
    052E:    77             RR       A
    052F:    72 70          JB3      00070H
    0531:    BE 6A          MOV      R6, #06AH
    0533:    6A             ADD      A, R2
    0534:    64 71          JMP      00371H
    0536:    5E             ANL      A, R6
    0537:    CE             DEC      R6
    0538:    59             ANL      A, R1
    0539:    7B             ADDC     A, R3
    053A:    54 76          CALL     00276H
    053C:    4F             ORL      A, R7
    053D:    B9 4B          MOV      R1, #04BH
    053F:    3F             MOVD     P7, A
    0540:    47             SWAP     A
    0541:    06             ???      
    0542:    43 09          ORL      A, #009H
    0544:    3F             MOVD     P7, A
    0545:    46 3B          JNT1     0003BH
    0547:    B9 38          MOV      R1, #038H
    0549:    5F             ANL      A, R7
    054A:    35             DIS      TCNTI
    054B:    35             DIS      TCNTI
    054C:    32 38          JB1      00038H
    054E:    2F             XCH      A, R7
    054F:    67             RRC      A
    0550:    2C             XCH      A, R4
    0551:    BE 2A          MOV      R6, #02AH
    0553:    3B             ???      
    0554:    27             CLR      A
    0555:    DC             XRL      A, R4
    0556:    25             EN       TCNTI
    0557:    9F             ANLD     P7, A
    0558:    23 83          MOV      A, #083H
    055A:    21             XCH      A, @R1
    055B:    85             CLR      F0
    055C:    1F             INC      R7
    055D:    A3             MOVP     A, @A
    055E:    1D             INC      R5
    055F:    DD             XRL      A, R5
    0560:    1C             INC      R4
    0561:    2F             XCH      A, R7
    0562:    1A             INC      R2
    0563:    9B             ???      
    0564:    19             INC      R1
    0565:    1C             INC      R4
    0566:    17             INC      A
    0567:    B3             JMPP     @A
    0568:    16 5F          JTF      0005FH
    056A:    15             DIS      I
    056B:    1D             INC      R5
    056C:    13 EE          ADDC     A, #0EEH
    056E:    12 D0          JB0      000D0H
    0570:    11             INC      @R1
    0571:    C1             ???      
    0572:    10             INC      @R0
    0573:    C2             ???      
    0574:    0F             MOVD     A, P7
    0575:    D2 0E          JB6      0000EH
    0577:    EE 0E          DJNZ     R6, 0000EH
    0579:    18             INC      R0
    057A:    0D             MOVD     A, P5
    057B:    4D             ORL      A, R5
    057C:    0C             MOVD     A, P4
    057D:    8E             ORLD     P6, A
    057E:    0B             ???      
    057F:    DA             XRL      A, R2
    0580:    0B             ???      
    0581:    2F             XCH      A, R7
    0582:    0A             IN       A, P2
    0583:    8F             ORLD     P7, A
    0584:    09             IN       A, P1
    0585:    F7             RLC      A
    0586:    09             IN       A, P1
    0587:    68             ADD      A, R0
    0588:    08             INS      A, BUS
    0589:    E1             ???      
    058A:    08             INS      A, BUS
    058B:    61             ADD      A, @R1
    058C:    07             DEC      A
    058D:    E9 07          DJNZ     R1, 00007H
    058F:    77             RR       A
    0590:    07             DEC      A
    0591:    0C             MOVD     A, P4
    0592:    06             ???      
    0593:    A7             CPL      C
    0594:    06             ???      
    0595:    47             SWAP     A
    0596:    05             EN       I
    0597:    ED 05          DJNZ     R5, 00005H
    0599:    98 05          ANL      BUS, #005H
    059B:    47             SWAP     A
    059C:    04 FC          JMP      000FCH
    059E:    04 B4          JMP      000B4H
    05A0:    04 70          JMP      00070H
    05A2:    04 31          JMP      00031H
    05A4:    03 F4          ADD      A, #0F4H
    05A6:    03 BC          ADD      A, #0BCH
    05A8:    03 86          ADD      A, #086H
    05AA:    03 53          ADD      A, #053H
    05AC:    03 24          ADD      A, #024H
    05AE:    02             OUTL     BUS, A
    05AF:    F6 02          JC       00002H
    05B1:    CC             DEC      R4
    05B2:    02             OUTL     BUS, A
    05B3:    A4 02          JMP      00502H
    05B5:    7E             ADDC     A, R6
    05B6:    02             OUTL     BUS, A
    05B7:    5A             ANL      A, R2
    05B8:    02             OUTL     BUS, A
    05B9:    38             ???      
    05BA:    02             OUTL     BUS, A
    05BB:    18             INC      R0
    05BC:    01             ???      
    05BD:    FA             MOV      A, R2
    05BE:    01             ???      
    05BF:    DE             XRL      A, R6
    05C0:    01             ???      
    05C1:    C3             ???      
    05C2:    01             ???      
    05C3:    AA             MOV      R2, A
    05C4:    01             ???      
    05C5:    92 01          JB4      00001H
    05C7:    7B             ADDC     A, R3
    05C8:    01             ???      
    05C9:    66             ???      
    05CA:    01             ???      
    05CB:    52 01          JB2      00001H
    05CD:    3F             MOVD     P7, A
    05CE:    01             ???      
    05CF:    2D             XCH      A, R5
    05D0:    01             ???      
    05D1:    1C             INC      R4
    05D2:    01             ???      
    05D3:    0C             MOVD     A, P4
    05D4:    00             NOP      
    05D5:    FD             MOV      A, R5
    05D6:    00             NOP      
    05D7:    EF 00          DJNZ     R7, ___CL_0001
    05D9:    E1             ???      
    05DA:    00             NOP      
    05DB:    D5             SEL      RB1
    05DC:    00             NOP      
    05DD:    C9             DEC      R1
    05DE:    00             NOP      
    05DF:    BE 00          MOV      R6, #000H
    05E1:    B3             JMPP     @A
    05E2:    00             NOP      
    05E3:    A9             MOV      R1, A
    05E4:    00             NOP      
    05E5:    9F             ANLD     P7, A
    05E6:    00             NOP      
    05E7:    96 00          JNZ      ___CL_0001
    05E9:    8E             ORLD     P6, A
    05EA:    00             NOP      
    05EB:    86 00          JNI      ___CL_0001
    05ED:    7F             ADDC     A, R7
    05EE:    00             NOP      
    05EF:    77             RR       A
    05F0:    00             NOP      
    05F1:    71             ADDC     A, @R1
    05F2:    00             NOP      
    05F3:    6A             ADD      A, R2
    05F4:    00             NOP      
    05F5:    64 00          JMP      00300H
    05F7:    5F             ANL      A, R7
    05F8:    00             NOP      
    05F9:    59             ANL      A, R1
    05FA:    00             NOP      
    05FB:    54 00          CALL     00200H
    05FD:    50             ANL      A, @R0
    05FE:    00             NOP      
    05FF:    4B             ORL      A, R3
    0600:    03 43          ADD      A, #043H
    0602:    01             ???      
    0603:    00             NOP      
    0604:    03 3D          ADD      A, #03DH
    0606:    01             ???      
    0607:    00             NOP      
    0608:    80             MOVX     A, @R0
    0609:    01             ???      
    060A:    77             RR       A
    060B:    01             ???      
    060C:    00             NOP      
    060D:    01             ???      
    060E:    73             ???      
    060F:    01             ???      
    0610:    00             NOP      
    0611:    89 B8          ORL      P1, #0B8H
    0613:    3D             MOVD     P5, A
    0614:    BA 50          MOV      R2, #050H
    0616:    F4 99          CALL     00799H
    0618:    B8 37          MOV      R0, #037H
    061A:    23 08          MOV      A, #008H
    061C:    90             MOVX     @R0, A
    061D:    27             CLR      A
    061E:    18             INC      R0
    061F:    90             MOVX     @R0, A
    0620:    B8 39          MOV      R0, #039H
    0622:    27             CLR      A
    0623:    90             MOVX     @R0, A
    0624:    18             INC      R0
    0625:    23 FF          MOV      A, #0FFH
    0627:    90             MOVX     @R0, A
    0628:    18             INC      R0
    0629:    27             CLR      A
    062A:    90             MOVX     @R0, A
    062B:    18             INC      R0
    062C:    23 08          MOV      A, #008H
    062E:    90             MOVX     @R0, A
    062F:    34 FC          CALL     001FCH
    0631:    B8 3E          MOV      R0, #03EH
    0633:    F4 25          CALL     00725H
    0635:    F6 EB          JC       000EBH
    0637:    B8 37          MOV      R0, #037H
    0639:    80             MOVX     A, @R0
    063A:    07             DEC      A
    063B:    90             MOVX     @R0, A
    063C:    96 47          JNZ      00047H
    063E:    23 08          MOV      A, #008H
    0640:    90             MOVX     @R0, A
    0641:    18             INC      R0
    0642:    80             MOVX     A, @R0
    0643:    07             DEC      A
    0644:    90             MOVX     @R0, A
    0645:    AF             MOV      R7, A
    0646:    A7             CPL      C
    0647:    B8 39          MOV      R0, #039H
    0649:    BA 08          MOV      R2, #008H
    064B:    B9 19          MOV      R1, #019H
    064D:    D4 7C          CALL     0067CH
    064F:    B8 3B          MOV      R0, #03BH
    0651:    BA 09          MOV      R2, #009H
    0653:    B9 1A          MOV      R1, #01AH
    0655:    D4 7C          CALL     0067CH
    0657:    BD 04          MOV      R5, #004H
    0659:    B9 1B          MOV      R1, #01BH
    065B:    F4 AC          CALL     007ACH
    065D:    E6 7A          JNC      0007AH
    065F:    C6 6D          JZ       0006DH
    0661:    FD             MOV      A, R5
    0662:    91             MOVX     @R1, A
    0663:    B8 0A          MOV      R0, #00AH
    0665:    23 01          MOV      A, #001H
    0667:    90             MOVX     @R0, A
    0668:    B8 40          MOV      R0, #040H
    066A:    80             MOVX     A, @R0
    066B:    76 70          JF1      00070H
    066D:    B6 7A          JF0      0007AH
    066F:    FE             MOV      A, R6
    0670:    03 FC          ADD      A, #0FCH
    0672:    F6 75          JC       00075H
    0674:    27             CLR      A
    0675:    B4 12          CALL     00512H
    0677:    B8 0E          MOV      R0, #00EH
    0679:    90             MOVX     @R0, A
    067A:    24 F4          JMP      001F4H
    067C:    BB 00          MOV      R3, #000H
    067E:    E6 81          JNC      00081H
    0680:    1B             INC      R3
    0681:    BD 04          MOV      R5, #004H
    0683:    F4 AC          CALL     007ACH
    0685:    F6 8B          JC       0008BH
    0687:    BD 00          MOV      R5, #000H
    0689:    76 97          JF1      00097H
    068B:    97             CLR      C
    068C:    C6 97          JZ       00097H
    068E:    FD             MOV      A, R5
    068F:    91             MOVX     @R1, A
    0690:    A7             CPL      C
    0691:    B9 38          MOV      R1, #038H
    0693:    81             MOVX     A, @R1
    0694:    AF             MOV      R7, A
    0695:    76 9B          JF1      0009BH
    0697:    FB             MOV      A, R3
    0698:    C6 9B          JZ       0009BH
    069A:    A7             CPL      C
    069B:    FA             MOV      A, R2
    069C:    A9             MOV      R1, A
    069D:    80             MOVX     A, @R0
    069E:    96 BE          JNZ      000BEH
    06A0:    18             INC      R0
    06A1:    80             MOVX     A, @R0
    06A2:    17             INC      A
    06A3:    AA             MOV      R2, A
    06A4:    A3             MOVP     A, @A
    06A5:    F2 BA          JB7      000BAH
    06A7:    C8             DEC      R0
    06A8:    90             MOVX     @R0, A
    06A9:    18             INC      R0
    06AA:    1A             INC      R2
    06AB:    FA             MOV      A, R2
    06AC:    90             MOVX     @R0, A
    06AD:    C8             DEC      R0
    06AE:    F8             MOV      A, R0
    06AF:    AC             MOV      R4, A
    06B0:    B8 38          MOV      R0, #038H
    06B2:    80             MOVX     A, @R0
    06B3:    AF             MOV      R7, A
    06B4:    FC             MOV      A, R4
    06B5:    A8             MOV      R0, A
    06B6:    97             CLR      C
    06B7:    A7             CPL      C
    06B8:    76 9D          JF1      0009DH
    06BA:    53 7F          ANL      A, #07FH
    06BC:    76 A3          JF1      000A3H
    06BE:    07             DEC      A
    06BF:    90             MOVX     @R0, A
    06C0:    E6 DC          JNC      000DCH
    06C2:    FD             MOV      A, R5
    06C3:    C6 D6          JZ       000D6H
    06C5:    18             INC      R0
    06C6:    80             MOVX     A, @R0
    06C7:    18             INC      R0
    06C8:    A3             MOVP     A, @A
    06C9:    C6 E1          JZ       000E1H
    06CB:    6F             ADD      A, R7
    06CC:    E7             RL       A
    06CD:    AB             MOV      R3, A
    06CE:    17             INC      A
    06CF:    B4 10          CALL     00510H
    06D1:    91             MOVX     @R1, A
    06D2:    FB             MOV      A, R3
    06D3:    B4 10          CALL     00510H
    06D5:    91             MOVX     @R1, A
    06D6:    B8 40          MOV      R0, #040H
    06D8:    80             MOVX     A, @R0
    06D9:    AE             MOV      R6, A
    06DA:    76 DE          JF1      000DEH
    06DC:    B6 EA          JF0      000EAH
    06DE:    FE             MOV      A, R6
    06DF:    B4 12          CALL     00512H
    06E1:    19             INC      R1
    06E2:    19             INC      R1
    06E3:    19             INC      R1
    06E4:    19             INC      R1
    06E5:    2D             XCH      A, R5
    06E6:    C6 EA          JZ       000EAH
    06E8:    2D             XCH      A, R5
    06E9:    91             MOVX     @R1, A
    06EA:    93             RETR     
    06EB:    BB 03          MOV      R3, #003H
    06ED:    BD 04          MOV      R5, #004H
    06EF:    B9 19          MOV      R1, #019H
    06F1:    B8 0C          MOV      R0, #00CH
    06F3:    F4 AC          CALL     007ACH
    06F5:    E6 FA          JNC      000FAH
    06F7:    27             CLR      A
    06F8:    90             MOVX     @R0, A
    06F9:    91             MOVX     @R1, A
    06FA:    18             INC      R0
    06FB:    19             INC      R1
    06FC:    EB F3          DJNZ     R3, 000F3H
    06FE:    24 F8          JMP      001F8H
    0700:    B9 10          MOV      R1, #010H
    0702:    23 CD          MOV      A, #0CDH
    0704:    91             MOVX     @R1, A
    0705:    23 37          MOV      A, #037H
    0707:    91             MOVX     @R1, A
    0708:    B9 14          MOV      R1, #014H
    070A:    76 1E          JF1      0001EH
    070C:    B9 11          MOV      R1, #011H
    070E:    23 06          MOV      A, #006H
    0710:    91             MOVX     @R1, A
    0711:    23 47          MOV      A, #047H
    0713:    91             MOVX     @R1, A
    0714:    B9 15          MOV      R1, #015H
    0716:    76 1E          JF1      0001EH
    0718:    B9 12          MOV      R1, #012H
    071A:    FE             MOV      A, R6
    071B:    91             MOVX     @R1, A
    071C:    B9 16          MOV      R1, #016H
    071E:    18             INC      R0
    071F:    18             INC      R0
    0720:    80             MOVX     A, @R0
    0721:    C8             DEC      R0
    0722:    C8             DEC      R0
    0723:    91             MOVX     @R1, A
    0724:    83             RET      
    0725:    85             CLR      F0
    0726:    95             CPL      F0
    0727:    80             MOVX     A, @R0
    0728:    07             DEC      A
    0729:    90             MOVX     @R0, A
    072A:    96 5B          JNZ      0005BH
    072C:    95             CPL      F0
    072D:    18             INC      R0
    072E:    80             MOVX     A, @R0
    072F:    A9             MOV      R1, A
    0730:    17             INC      A
    0731:    E3             MOVP3    A, @A
    0732:    AE             MOV      R6, A
    0733:    18             INC      R0
    0734:    80             MOVX     A, @R0
    0735:    6E             ADD      A, R6
    0736:    90             MOVX     @R0, A
    0737:    AE             MOV      R6, A
    0738:    C8             DEC      R0
    0739:    C8             DEC      R0
    073A:    C8             DEC      R0
    073B:    80             MOVX     A, @R0
    073C:    07             DEC      A
    073D:    90             MOVX     @R0, A
    073E:    18             INC      R0
    073F:    96 58          JNZ      00058H
    0741:    19             INC      R1
    0742:    19             INC      R1
    0743:    F9             MOV      A, R1
    0744:    E3             MOVP3    A, @A
    0745:    96 50          JNZ      00050H
    0747:    F9             MOV      A, R1
    0748:    17             INC      A
    0749:    E3             MOVP3    A, @A
    074A:    A9             MOV      R1, A
    074B:    96 44          JNZ      00044H
    074D:    97             CLR      C
    074E:    A7             CPL      C
    074F:    83             RET      
    0750:    19             INC      R1
    0751:    C8             DEC      R0
    0752:    90             MOVX     @R0, A
    0753:    18             INC      R0
    0754:    18             INC      R0
    0755:    F9             MOV      A, R1
    0756:    90             MOVX     @R0, A
    0757:    C8             DEC      R0
    0758:    F9             MOV      A, R1
    0759:    E3             MOVP3    A, @A
    075A:    90             MOVX     @R0, A
    075B:    97             CLR      C
    075C:    83             RET      
    075D:    85             CLR      F0
    075E:    95             CPL      F0
    075F:    80             MOVX     A, @R0
    0760:    07             DEC      A
    0761:    90             MOVX     @R0, A
    0762:    96 97          JNZ      00097H
    0764:    95             CPL      F0
    0765:    18             INC      R0
    0766:    80             MOVX     A, @R0
    0767:    A9             MOV      R1, A
    0768:    17             INC      A
    0769:    94 4E          CALL     0044EH
    076B:    AE             MOV      R6, A
    076C:    18             INC      R0
    076D:    80             MOVX     A, @R0
    076E:    6E             ADD      A, R6
    076F:    90             MOVX     @R0, A
    0770:    AE             MOV      R6, A
    0771:    C8             DEC      R0
    0772:    C8             DEC      R0
    0773:    C8             DEC      R0
    0774:    80             MOVX     A, @R0
    0775:    07             DEC      A
    0776:    90             MOVX     @R0, A
    0777:    18             INC      R0
    0778:    96 93          JNZ      00093H
    077A:    19             INC      R1
    077B:    19             INC      R1
    077C:    F9             MOV      A, R1
    077D:    94 4E          CALL     0044EH
    077F:    96 8B          JNZ      0008BH
    0781:    F9             MOV      A, R1
    0782:    17             INC      A
    0783:    94 4E          CALL     0044EH
    0785:    A9             MOV      R1, A
    0786:    96 7D          JNZ      0007DH
    0788:    97             CLR      C
    0789:    A7             CPL      C
    078A:    83             RET      
    078B:    19             INC      R1
    078C:    C8             DEC      R0
    078D:    90             MOVX     @R0, A
    078E:    18             INC      R0
    078F:    18             INC      R0
    0790:    F9             MOV      A, R1
    0791:    90             MOVX     @R0, A
    0792:    C8             DEC      R0
    0793:    F9             MOV      A, R1
    0794:    94 4E          CALL     0044EH
    0796:    90             MOVX     @R0, A
    0797:    97             CLR      C
    0798:    83             RET      
    0799:    23 01          MOV      A, #001H
    079B:    90             MOVX     @R0, A
    079C:    18             INC      R0
    079D:    90             MOVX     @R0, A
    079E:    18             INC      R0
    079F:    FA             MOV      A, R2
    07A0:    1A             INC      R2
    07A1:    94 4E          CALL     0044EH
    07A3:    90             MOVX     @R0, A
    07A4:    18             INC      R0
    07A5:    FA             MOV      A, R2
    07A6:    1A             INC      R2
    07A7:    94 4E          CALL     0044EH
    07A9:    90             MOVX     @R0, A
    07AA:    18             INC      R0
    07AB:    83             RET      
    07AC:    81             MOVX     A, @R1
    07AD:    C6 B3          JZ       000B3H
    07AF:    37             CPL      A
    07B0:    17             INC      A
    07B1:    6D             ADD      A, R5
    07B2:    83             RET      
    07B3:    97             CLR      C
    07B4:    A7             CPL      C
    07B5:    17             INC      A
    07B6:    83             RET      
    07B7:    A3             MOVP     A, @A
    07B8:    83             RET      
    07B9:    96 2F          JNZ      0002FH
    07BB:    67             RRC      A
    07BC:    2F             XCH      A, R7
    07BD:    C9             DEC      R1
    07BE:    17             INC      A
    07BF:    B3             JMPP     @A
    07C0:    17             INC      A
    07C1:    DA             XRL      A, R2
    07C2:    0B             ???      
    07C3:    E0             ???      
    07C4:    0B             ???      
    07C5:    06             ???      
    07C6:    47             SWAP     A
    07C7:    B0 46          MOV      @R0, #046H
    07C9:    94 23          CALL     00423H
    07CB:    83             RET      
    07CC:    23 C1          MOV      A, #0C1H
    07CE:    11             INC      @R1
    07CF:    CB             DEC      R3
    07D0:    11             INC      @R1
    07D1:    83             RET      
    07D2:    23 A2          MOV      A, #0A2H
    07D4:    23 C1          MOV      A, #0C1H
    07D6:    11             INC      @R1
    07D7:    DB             XRL      A, R3
    07D8:    11             INC      @R1
    07D9:    E1             ???      
    07DA:    08             INS      A, BUS
    07DB:    E6 08          JNC      00008H
    07DD:    23 01          MOV      A, #001H
    07DF:    91             MOVX     @R1, A
    07E0:    19             INC      R1
    07E1:    91             MOVX     @R1, A
    07E2:    19             INC      R1
    07E3:    FA             MOV      A, R2
    07E4:    1A             INC      R2
    07E5:    94 4E          CALL     0044EH
    07E7:    91             MOVX     @R1, A
    07E8:    19             INC      R1
    07E9:    80             MOVX     A, @R0
    07EA:    96 F0          JNZ      000F0H
    07EC:    FA             MOV      A, R2
    07ED:    94 4E          CALL     0044EH
    07EF:    91             MOVX     @R1, A
    07F0:    1A             INC      R2
    07F1:    19             INC      R1
    07F2:    83             RET      
    07F3:    8C             ORLD     P4, A
    07F4:    C8             DEC      R0
    07F5:    8C             ORLD     P4, A
    07F6:    C8             DEC      R0
    07F7:    8C             ORLD     P4, A
    07F8:    C8             DEC      R0
    07F9:    8C             ORLD     P4, A
    07FA:    C8             DEC      R0
    07FB:    8C             ORLD     P4, A
    07FC:    C8             DEC      R0
    07FD:    8C             ORLD     P4, A
    07FE:    C8             DEC      R0
    07FF:    8C             ORLD     P4, A
    0800:    B8 41          MOV      R0, #041H
    0802:    BA 52          MOV      R2, #052H
    0804:    F4 99          CALL     00799H
    0806:    F4 99          CALL     00799H
    0808:    F4 99          CALL     00799H
    080A:    23 01          MOV      A, #001H
    080C:    B8 07          MOV      R0, #007H
    080E:    90             MOVX     @R0, A
    080F:    34 FC          CALL     001FCH
    0811:    B9 18          MOV      R1, #018H
    0813:    BD 06          MOV      R5, #006H
    0815:    F4 AC          CALL     007ACH
    0817:    F6 1D          JC       0001DH
    0819:    BD 00          MOV      R5, #000H
    081B:    76 28          JF1      00028H
    081D:    C6 28          JZ       00028H
    081F:    FD             MOV      A, R5
    0820:    91             MOVX     @R1, A
    0821:    BD FF          MOV      R5, #0FFH
    0823:    B8 02          MOV      R0, #002H
    0825:    23 31          MOV      A, #031H
    0827:    90             MOVX     @R0, A
    0828:    B8 42          MOV      R0, #042H
    082A:    F4 25          CALL     00725H
    082C:    F6 91          JC       00091H
    082E:    FD             MOV      A, R5
    082F:    F2 87          JB7      00087H
    0831:    C6 74          JZ       00074H
    0833:    B6 3D          JF0      0003DH
    0835:    FE             MOV      A, R6
    0836:    B4 12          CALL     00512H
    0838:    B9 04          MOV      R1, #004H
    083A:    91             MOVX     @R1, A
    083B:    19             INC      R1
    083C:    91             MOVX     @R1, A
    083D:    B8 46          MOV      R0, #046H
    083F:    F4 25          CALL     00725H
    0841:    BA 03          MOV      R2, #003H
    0843:    42             MOV      A, T
    0844:    53 1F          ANL      A, #01FH
    0846:    32 4F          JB1      0004FH
    0848:    03 24          ADD      A, #024H
    084A:    E6 55          JNC      00055H
    084C:    1A             INC      R2
    084D:    76 55          JF1      00055H
    084F:    37             CPL      A
    0850:    03 25          ADD      A, #025H
    0852:    F6 55          JC       00055H
    0854:    CA             DEC      R2
    0855:    AB             MOV      R3, A
    0856:    B9 48          MOV      R1, #048H
    0858:    81             MOVX     A, @R1
    0859:    F2 61          JB7      00061H
    085B:    6B             ADD      A, R3
    085C:    E6 65          JNC      00065H
    085E:    1A             INC      R2
    085F:    76 65          JF1      00065H
    0861:    6B             ADD      A, R3
    0862:    F6 65          JC       00065H
    0864:    CA             DEC      R2
    0865:    AB             MOV      R3, A
    0866:    B8 00          MOV      R0, #000H
    0868:    90             MOVX     @R0, A
    0869:    FA             MOV      A, R2
    086A:    90             MOVX     @R0, A
    086B:    18             INC      R0
    086C:    FB             MOV      A, R3
    086D:    03 6E          ADD      A, #06EH
    086F:    90             MOVX     @R0, A
    0870:    FA             MOV      A, R2
    0871:    13 FE          ADDC     A, #0FEH
    0873:    90             MOVX     @R0, A
    0874:    B8 4A          MOV      R0, #04AH
    0876:    F4 25          CALL     00725H
    0878:    FD             MOV      A, R5
    0879:    F2 8C          JB7      0008CH
    087B:    C6 85          JZ       00085H
    087D:    B6 85          JF0      00085H
    087F:    FE             MOV      A, R6
    0880:    B4 12          CALL     00512H
    0882:    B8 06          MOV      R0, #006H
    0884:    90             MOVX     @R0, A
    0885:    24 F4          JMP      001F4H
    0887:    B8 44          MOV      R0, #044H
    0889:    80             MOVX     A, @R0
    088A:    76 36          JF1      00036H
    088C:    B8 4C          MOV      R0, #04CH
    088E:    80             MOVX     A, @R0
    088F:    76 80          JF1      00080H
    0891:    FD             MOV      A, R5
    0892:    C6 9F          JZ       0009FH
    0894:    B8 04          MOV      R0, #004H
    0896:    27             CLR      A
    0897:    90             MOVX     @R0, A
    0898:    18             INC      R0
    0899:    90             MOVX     @R0, A
    089A:    18             INC      R0
    089B:    90             MOVX     @R0, A
    089C:    B9 18          MOV      R1, #018H
    089E:    91             MOVX     @R1, A
    089F:    24 F8          JMP      001F8H
    08A1:    B8 4D          MOV      R0, #04DH
    08A3:    BA 7F          MOV      R2, #07FH
    08A5:    F4 99          CALL     00799H
    08A7:    F4 99          CALL     00799H
    08A9:    B9 02          MOV      R1, #002H
    08AB:    23 3B          MOV      A, #03BH
    08AD:    91             MOVX     @R1, A
    08AE:    B9 07          MOV      R1, #007H
    08B0:    23 01          MOV      A, #001H
    08B2:    91             MOVX     @R1, A
    08B3:    34 FC          CALL     001FCH
    08B5:    B8 4E          MOV      R0, #04EH
    08B7:    F4 5D          CALL     0075DH
    08B9:    F6 DE          JC       000DEH
    08BB:    B6 C6          JF0      000C6H
    08BD:    42             MOV      A, T
    08BE:    53 01          ANL      A, #001H
    08C0:    6E             ADD      A, R6
    08C1:    B4 12          CALL     00512H
    08C3:    B9 05          MOV      R1, #005H
    08C5:    91             MOVX     @R1, A
    08C6:    B8 52          MOV      R0, #052H
    08C8:    F4 5D          CALL     0075DH
    08CA:    B6 DC          JF0      000DCH
    08CC:    B9 01          MOV      R1, #001H
    08CE:    FE             MOV      A, R6
    08CF:    E7             RL       A
    08D0:    53 FE          ANL      A, #0FEH
    08D2:    03 90          ADD      A, #090H
    08D4:    91             MOVX     @R1, A
    08D5:    FE             MOV      A, R6
    08D6:    E7             RL       A
    08D7:    53 01          ANL      A, #001H
    08D9:    13 01          ADDC     A, #001H
    08DB:    91             MOVX     @R1, A
    08DC:    24 F4          JMP      001F4H
    08DE:    27             CLR      A
    08DF:    B9 05          MOV      R1, #005H
    08E1:    91             MOVX     @R1, A
    08E2:    24 F8          JMP      001F8H
    08E4:    C8             DEC      R0
    08E5:    8C             ORLD     P4, A
    08E6:    C8             DEC      R0
    08E7:    8C             ORLD     P4, A
    08E8:    C8             DEC      R0
    08E9:    8C             ORLD     P4, A
    08EA:    C8             DEC      R0
    08EB:    8C             ORLD     P4, A
    08EC:    C8             DEC      R0
    08ED:    8C             ORLD     P4, A
    08EE:    C8             DEC      R0
    08EF:    8C             ORLD     P4, A
    08F0:    C8             DEC      R0
    08F1:    8C             ORLD     P4, A
    08F2:    C8             DEC      R0
    08F3:    8C             ORLD     P4, A
    08F4:    C8             DEC      R0
    08F5:    8C             ORLD     P4, A
    08F6:    C8             DEC      R0
    08F7:    8C             ORLD     P4, A
    08F8:    C8             DEC      R0
    08F9:    8C             ORLD     P4, A
    08FA:    C8             DEC      R0
    08FB:    8C             ORLD     P4, A
    08FC:    C8             DEC      R0
    08FD:    8C             ORLD     P4, A
    08FE:    C8             DEC      R0
    08FF:    8C             ORLD     P4, A
    0900:    B9 1A          MOV      R1, #01AH
    0902:    23 06          MOV      A, #006H
    0904:    91             MOVX     @R1, A
    0905:    B8 0D          MOV      R0, #00DH
    0907:    23 48          MOV      A, #048H
    0909:    90             MOVX     @R0, A
    090A:    B9 22          MOV      R1, #022H
    090C:    B1 9A          MOV      @R1, #09AH
    090E:    19             INC      R1
    090F:    B1 08          MOV      @R1, #008H
    0911:    34 FC          CALL     001FCH
    0913:    B8 09          MOV      R0, #009H
    0915:    B9 22          MOV      R1, #022H
    0917:    F1             MOV      A, @R1
    0918:    03 FD          ADD      A, #0FDH
    091A:    A1             MOV      @R1, A
    091B:    19             INC      R1
    091C:    90             MOVX     @R0, A
    091D:    F1             MOV      A, @R1
    091E:    F6 22          JC       00022H
    0920:    07             DEC      A
    0921:    A1             MOV      @R1, A
    0922:    90             MOVX     @R0, A
    0923:    D3 04          XRL      A, #004H
    0925:    96 32          JNZ      00032H
    0927:    C9             DEC      R1
    0928:    F1             MOV      A, @R1
    0929:    D3 B0          XRL      A, #0B0H
    092B:    96 32          JNZ      00032H
    092D:    B1 9A          MOV      @R1, #09AH
    092F:    19             INC      R1
    0930:    B1 08          MOV      @R1, #008H
    0932:    24 F4          JMP      001F4H
    0934:    27             CLR      A
    0935:    B8 1A          MOV      R0, #01AH
    0937:    90             MOVX     @R0, A
    0938:    B8 0D          MOV      R0, #00DH
    093A:    90             MOVX     @R0, A
    093B:    24 F8          JMP      001F8H
    093D:    B9 1C          MOV      R1, #01CH
    093F:    BD 05          MOV      R5, #005H
    0941:    FD             MOV      A, R5
    0942:    91             MOVX     @R1, A
    0943:    B8 14          MOV      R0, #014H
    0945:    23 6B          MOV      A, #06BH
    0947:    90             MOVX     @R0, A
    0948:    B8 10          MOV      R0, #010H
    094A:    23 C9          MOV      A, #0C9H
    094C:    90             MOVX     @R0, A
    094D:    23 01          MOV      A, #001H
    094F:    90             MOVX     @R0, A
    0950:    19             INC      R1
    0951:    F4 AC          CALL     007ACH
    0953:    E6 64          JNC      00064H
    0955:    FD             MOV      A, R5
    0956:    91             MOVX     @R1, A
    0957:    B8 15          MOV      R0, #015H
    0959:    23 11          MOV      A, #011H
    095B:    90             MOVX     @R0, A
    095C:    B8 11          MOV      R0, #011H
    095E:    23 41          MOV      A, #041H
    0960:    90             MOVX     @R0, A
    0961:    23 03          MOV      A, #003H
    0963:    90             MOVX     @R0, A
    0964:    B8 24          MOV      R0, #024H
    0966:    B0 DD          MOV      @R0, #0DDH
    0968:    34 FC          CALL     001FCH
    096A:    B8 24          MOV      R0, #024H
    096C:    10             INC      @R0
    096D:    F0             MOV      A, @R0
    096E:    C6 72          JZ       00072H
    0970:    24 F4          JMP      001F4H
    0972:    B9 1C          MOV      R1, #01CH
    0974:    91             MOVX     @R1, A
    0975:    B8 14          MOV      R0, #014H
    0977:    90             MOVX     @R0, A
    0978:    19             INC      R1
    0979:    BD 05          MOV      R5, #005H
    097B:    F4 AC          CALL     007ACH
    097D:    E6 84          JNC      00084H
    097F:    96 84          JNZ      00084H
    0981:    91             MOVX     @R1, A
    0982:    18             INC      R0
    0983:    90             MOVX     @R0, A
    0984:    24 F8          JMP      001F8H
    0986:    BA 9C          MOV      R2, #09CH
    0988:    BB B9          MOV      R3, #0B9H
    098A:    76 96          JF1      00096H
    098C:    BA 9E          MOV      R2, #09EH
    098E:    BB C5          MOV      R3, #0C5H
    0990:    76 96          JF1      00096H
    0992:    BA A0          MOV      R2, #0A0H
    0994:    BB D1          MOV      R3, #0D1H
    0996:    B9 25          MOV      R1, #025H
    0998:    B1 FF          MOV      @R1, #0FFH
    099A:    B8 55          MOV      R0, #055H
    099C:    F4 99          CALL     00799H
    099E:    B8 00          MOV      R0, #000H
    09A0:    BC 03          MOV      R4, #003H
    09A2:    BD 02          MOV      R5, #002H
    09A4:    FB             MOV      A, R3
    09A5:    1B             INC      R3
    09A6:    F4 B7          CALL     007B7H
    09A8:    90             MOVX     @R0, A
    09A9:    FB             MOV      A, R3
    09AA:    1B             INC      R3
    09AB:    F4 B7          CALL     007B7H
    09AD:    90             MOVX     @R0, A
    09AE:    18             INC      R0
    09AF:    ED A4          DJNZ     R5, 000A4H
    09B1:    23 01          MOV      A, #001H
    09B3:    90             MOVX     @R0, A
    09B4:    F8             MOV      A, R0
    09B5:    03 05          ADD      A, #005H
    09B7:    A8             MOV      R0, A
    09B8:    23 01          MOV      A, #001H
    09BA:    90             MOVX     @R0, A
    09BB:    18             INC      R0
    09BC:    EC A2          DJNZ     R4, 000A2H
    09BE:    34 F6          CALL     001F6H
    09C0:    B9 25          MOV      R1, #025H
    09C2:    B1 00          MOV      @R1, #000H
    09C4:    34 FC          CALL     001FCH
    09C6:    B9 25          MOV      R1, #025H
    09C8:    F1             MOV      A, @R1
    09C9:    96 F8          JNZ      000F8H
    09CB:    B8 56          MOV      R0, #056H
    09CD:    F4 5D          CALL     0075DH
    09CF:    F6 E7          JC       000E7H
    09D1:    B6 E5          JF0      000E5H
    09D3:    FE             MOV      A, R6
    09D4:    B4 12          CALL     00512H
    09D6:    AE             MOV      R6, A
    09D7:    BB 03          MOV      R3, #003H
    09D9:    B8 04          MOV      R0, #004H
    09DB:    FE             MOV      A, R6
    09DC:    90             MOVX     @R0, A
    09DD:    18             INC      R0
    09DE:    90             MOVX     @R0, A
    09DF:    F8             MOV      A, R0
    09E0:    03 07          ADD      A, #007H
    09E2:    A8             MOV      R0, A
    09E3:    EB DB          DJNZ     R3, 000DBH
    09E5:    24 F4          JMP      001F4H
    09E7:    B8 04          MOV      R0, #004H
    09E9:    BD 03          MOV      R5, #003H
    09EB:    27             CLR      A
    09EC:    90             MOVX     @R0, A
    09ED:    18             INC      R0
    09EE:    90             MOVX     @R0, A
    09EF:    18             INC      R0
    09F0:    18             INC      R0
    09F1:    90             MOVX     @R0, A
    09F2:    F8             MOV      A, R0
    09F3:    03 05          ADD      A, #005H
    09F5:    A8             MOV      R0, A
    09F6:    ED EB          DJNZ     R5, 000EBH
    09F8:    24 F8          JMP      001F8H
    09FA:    01             ???      
    09FB:    8C             ORLD     P4, A
    09FC:    C8             DEC      R0
    09FD:    8C             ORLD     P4, A
    09FE:    C8             DEC      R0
    09FF:    8C             ORLD     P4, A
    0A00:    B8 6A          MOV      R0, #06AH
    0A02:    BA AA          MOV      R2, #0AAH
    0A04:    BF 23          MOV      R7, #023H
    0A06:    76 16          JF1      00016H
    0A08:    B8 5A          MOV      R0, #05AH
    0A0A:    BA A2          MOV      R2, #0A2H
    0A0C:    BF 21          MOV      R7, #021H
    0A0E:    76 16          JF1      00016H
    0A10:    B8 62          MOV      R0, #062H
    0A12:    BA A6          MOV      R2, #0A6H
    0A14:    BF 22          MOV      R7, #022H
    0A16:    B9 1B          MOV      R1, #01BH
    0A18:    23 06          MOV      A, #006H
    0A1A:    91             MOVX     @R1, A
    0A1B:    F4 99          CALL     00799H
    0A1D:    F4 99          CALL     00799H
    0A1F:    FF             MOV      A, R7
    0A20:    B3             JMPP     @A
    0A21:    36 2C          JT0      0002CH
    0A23:    24 34          JMP      00134H
    0A25:    FC             MOV      A, R4
    0A26:    B8 6B          MOV      R0, #06BH
    0A28:    BF 30          MOV      R7, #030H
    0A2A:    76 3C          JF1      0003CH
    0A2C:    34 FC          CALL     001FCH
    0A2E:    B8 63          MOV      R0, #063H
    0A30:    BF 20          MOV      R7, #020H
    0A32:    BD 01          MOV      R5, #001H
    0A34:    76 3C          JF1      0003CH
    0A36:    34 FC          CALL     001FCH
    0A38:    B8 5B          MOV      R0, #05BH
    0A3A:    BF 10          MOV      R7, #010H
    0A3C:    B9 59          MOV      R1, #059H
    0A3E:    81             MOVX     A, @R1
    0A3F:    53 F0          ANL      A, #0F0H
    0A41:    DF             XRL      A, R7
    0A42:    BD 00          MOV      R5, #000H
    0A44:    96 47          JNZ      00047H
    0A46:    1D             INC      R5
    0A47:    F4 25          CALL     00725H
    0A49:    F6 B6          JC       000B6H
    0A4B:    18             INC      R0
    0A4C:    18             INC      R0
    0A4D:    80             MOVX     A, @R0
    0A4E:    AE             MOV      R6, A
    0A4F:    18             INC      R0
    0A50:    18             INC      R0
    0A51:    B9 59          MOV      R1, #059H
    0A53:    FD             MOV      A, R5
    0A54:    C6 5A          JZ       0005AH
    0A56:    B6 9F          JF0      0009FH
    0A58:    76 65          JF1      00065H
    0A5A:    81             MOVX     A, @R1
    0A5B:    53 0F          ANL      A, #00FH
    0A5D:    C6 64          JZ       00064H
    0A5F:    37             CPL      A
    0A60:    17             INC      A
    0A61:    6E             ADD      A, R6
    0A62:    E6 9F          JNC      0009FH
    0A64:    CD             DEC      R5
    0A65:    FE             MOV      A, R6
    0A66:    4F             ORL      A, R7
    0A67:    91             MOVX     @R1, A
    0A68:    FE             MOV      A, R6
    0A69:    B4 12          CALL     00512H
    0A6B:    B9 0E          MOV      R1, #00EH
    0A6D:    91             MOVX     @R1, A
    0A6E:    AB             MOV      R3, A
    0A6F:    B9 1E          MOV      R1, #01EH
    0A71:    81             MOVX     A, @R1
    0A72:    96 7D          JNZ      0007DH
    0A74:    B9 16          MOV      R1, #016H
    0A76:    FB             MOV      A, R3
    0A77:    91             MOVX     @R1, A
    0A78:    B9 12          MOV      R1, #012H
    0A7A:    23 3F          MOV      A, #03FH
    0A7C:    91             MOVX     @R1, A
    0A7D:    B9 19          MOV      R1, #019H
    0A7F:    81             MOVX     A, @R1
    0A80:    96 8E          JNZ      0008EH
    0A82:    B9 0C          MOV      R1, #00CH
    0A84:    FB             MOV      A, R3
    0A85:    91             MOVX     @R1, A
    0A86:    B9 08          MOV      R1, #008H
    0A88:    23 C7          MOV      A, #0C7H
    0A8A:    91             MOVX     @R1, A
    0A8B:    23 58          MOV      A, #058H
    0A8D:    91             MOVX     @R1, A
    0A8E:    B9 1A          MOV      R1, #01AH
    0A90:    81             MOVX     A, @R1
    0A91:    96 9F          JNZ      0009FH
    0A93:    B9 0D          MOV      R1, #00DH
    0A95:    FB             MOV      A, R3
    0A96:    91             MOVX     @R1, A
    0A97:    B9 09          MOV      R1, #009H
    0A99:    23 AD          MOV      A, #0ADH
    0A9B:    91             MOVX     @R1, A
    0A9C:    23 90          MOV      A, #090H
    0A9E:    91             MOVX     @R1, A
    0A9F:    F4 25          CALL     00725H
    0AA1:    F6 B6          JC       000B6H
    0AA3:    FD             MOV      A, R5
    0AA4:    C6 B4          JZ       000B4H
    0AA6:    F2 AC          JB7      000ACH
    0AA8:    B6 B4          JF0      000B4H
    0AAA:    76 B0          JF1      000B0H
    0AAC:    18             INC      R0
    0AAD:    18             INC      R0
    0AAE:    80             MOVX     A, @R0
    0AAF:    AE             MOV      R6, A
    0AB0:    B9 0A          MOV      R1, #00AH
    0AB2:    FE             MOV      A, R6
    0AB3:    91             MOVX     @R1, A
    0AB4:    24 F4          JMP      001F4H
    0AB6:    FD             MOV      A, R5
    0AB7:    C6 D8          JZ       000D8H
    0AB9:    27             CLR      A
    0ABA:    B9 59          MOV      R1, #059H
    0ABC:    91             MOVX     @R1, A
    0ABD:    B9 0E          MOV      R1, #00EH
    0ABF:    91             MOVX     @R1, A
    0AC0:    B9 1E          MOV      R1, #01EH
    0AC2:    81             MOVX     A, @R1
    0AC3:    96 C8          JNZ      000C8H
    0AC5:    B9 16          MOV      R1, #016H
    0AC7:    91             MOVX     @R1, A
    0AC8:    B9 19          MOV      R1, #019H
    0ACA:    81             MOVX     A, @R1
    0ACB:    96 D0          JNZ      000D0H
    0ACD:    B9 0C          MOV      R1, #00CH
    0ACF:    91             MOVX     @R1, A
    0AD0:    B9 1A          MOV      R1, #01AH
    0AD2:    81             MOVX     A, @R1
    0AD3:    96 D8          JNZ      000D8H
    0AD5:    B9 0D          MOV      R1, #00DH
    0AD7:    91             MOVX     @R1, A
    0AD8:    B9 1B          MOV      R1, #01BH
    0ADA:    91             MOVX     @R1, A
    0ADB:    24 F8          JMP      001F8H
    0ADD:    8C             ORLD     P4, A
    0ADE:    C8             DEC      R0
    0ADF:    8C             ORLD     P4, A
    0AE0:    C8             DEC      R0
    0AE1:    8C             ORLD     P4, A
    0AE2:    C8             DEC      R0
    0AE3:    8C             ORLD     P4, A
    0AE4:    C8             DEC      R0
    0AE5:    8C             ORLD     P4, A
    0AE6:    C8             DEC      R0
    0AE7:    8C             ORLD     P4, A
    0AE8:    C8             DEC      R0
    0AE9:    06             ???      
    0AEA:    01             ???      
    0AEB:    8C             ORLD     P4, A
    0AEC:    C8             DEC      R0
    0AED:    8C             ORLD     P4, A
    0AEE:    C8             DEC      R0
    0AEF:    8C             ORLD     P4, A
    0AF0:    C8             DEC      R0
    0AF1:    8C             ORLD     P4, A
    0AF2:    C8             DEC      R0
    0AF3:    8C             ORLD     P4, A
    0AF4:    C8             DEC      R0
    0AF5:    8C             ORLD     P4, A
    0AF6:    C8             DEC      R0
    0AF7:    8C             ORLD     P4, A
    0AF8:    C8             DEC      R0
    0AF9:    8C             ORLD     P4, A
    0AFA:    C8             DEC      R0
    0AFB:    8C             ORLD     P4, A
    0AFC:    C8             DEC      R0
    0AFD:    8C             ORLD     P4, A
    0AFE:    C8             DEC      R0
    0AFF:    8C             ORLD     P4, A
    0B00:    B8 72          MOV      R0, #072H
    0B02:    80             MOVX     A, @R0
    0B03:    96 10          JNZ      00010H
    0B05:    B9 07          MOV      R1, #007H
    0B07:    23 01          MOV      A, #001H
    0B09:    91             MOVX     @R1, A
    0B0A:    B9 73          MOV      R1, #073H
    0B0C:    BA AE          MOV      R2, #0AEH
    0B0E:    F4 DD          CALL     007DDH
    0B10:    BA B0          MOV      R2, #0B0H
    0B12:    76 1B          JF1      0001BH
    0B14:    B8 72          MOV      R0, #072H
    0B16:    80             MOVX     A, @R0
    0B17:    C6 CD          JZ       000CDH
    0B19:    BA B6          MOV      R2, #0B6H
    0B1B:    B9 77          MOV      R1, #077H
    0B1D:    F4 DD          CALL     007DDH
    0B1F:    F4 DD          CALL     007DDH
    0B21:    F4 DD          CALL     007DDH
    0B23:    80             MOVX     A, @R0
    0B24:    96 32          JNZ      00032H
    0B26:    B8 26          MOV      R0, #026H
    0B28:    B0 FF          MOV      @R0, #0FFH
    0B2A:    B8 27          MOV      R0, #027H
    0B2C:    BA 06          MOV      R2, #006H
    0B2E:    B0 00          MOV      @R0, #000H
    0B30:    EA 2E          DJNZ     R2, 0002EH
    0B32:    B8 72          MOV      R0, #072H
    0B34:    23 80          MOV      A, #080H
    0B36:    90             MOVX     @R0, A
    0B37:    34 FC          CALL     001FCH
    0B39:    F5             SEL      MB1
    0B3A:    74 DD          CALL     003DDH
    0B3C:    E5             SEL      MB0
    0B3D:    B8 78          MOV      R0, #078H
    0B3F:    F4 25          CALL     00725H
    0B41:    B6 59          JF0      00059H
    0B43:    FE             MOV      A, R6
    0B44:    F2 8B          JB7      0008BH
    0B46:    03 F7          ADD      A, #0F7H
    0B48:    E6 50          JNC      00050H
    0B4A:    BE 08          MOV      R6, #008H
    0B4C:    B8 7A          MOV      R0, #07AH
    0B4E:    FE             MOV      A, R6
    0B4F:    90             MOVX     @R0, A
    0B50:    FD             MOV      A, R5
    0B51:    C6 59          JZ       00059H
    0B53:    FE             MOV      A, R6
    0B54:    B4 12          CALL     00512H
    0B56:    B8 04          MOV      R0, #004H
    0B58:    90             MOVX     @R0, A
    0B59:    B8 7C          MOV      R0, #07CH
    0B5B:    F4 25          CALL     00725H
    0B5D:    B6 73          JF0      00073H
    0B5F:    FE             MOV      A, R6
    0B60:    F2 8F          JB7      0008FH
    0B62:    03 D0          ADD      A, #0D0H
    0B64:    E6 6C          JNC      0006CH
    0B66:    BE 2F          MOV      R6, #02FH
    0B68:    B8 7E          MOV      R0, #07EH
    0B6A:    FE             MOV      A, R6
    0B6B:    90             MOVX     @R0, A
    0B6C:    B8 27          MOV      R0, #027H
    0B6E:    10             INC      @R0
    0B6F:    18             INC      R0
    0B70:    18             INC      R0
    0B71:    FE             MOV      A, R6
    0B72:    A0             MOV      @R0, A
    0B73:    B8 80          MOV      R0, #080H
    0B75:    F4 25          CALL     00725H
    0B77:    F6 93          JC       00093H
    0B79:    B6 9B          JF0      0009BH
    0B7B:    FE             MOV      A, R6
    0B7C:    03 05          ADD      A, #005H
    0B7E:    E6 86          JNC      00086H
    0B80:    BE FA          MOV      R6, #0FAH
    0B82:    B8 82          MOV      R0, #082H
    0B84:    FE             MOV      A, R6
    0B85:    90             MOVX     @R0, A
    0B86:    FE             MOV      A, R6
    0B87:    C6 CD          JZ       000CDH
    0B89:    76 9E          JF1      0009EH
    0B8B:    BE 00          MOV      R6, #000H
    0B8D:    76 4C          JF1      0004CH
    0B8F:    BE 00          MOV      R6, #000H
    0B91:    76 68          JF1      00068H
    0B93:    34 FC          CALL     001FCH
    0B95:    F5             SEL      MB1
    0B96:    74 DD          CALL     003DDH
    0B98:    E5             SEL      MB0
    0B99:    B8 80          MOV      R0, #080H
    0B9B:    18             INC      R0
    0B9C:    18             INC      R0
    0B9D:    80             MOVX     A, @R0
    0B9E:    B8 26          MOV      R0, #026H
    0BA0:    60             ADD      A, @R0
    0BA1:    A0             MOV      @R0, A
    0BA2:    E6 CB          JNC      000CBH
    0BA4:    B8 74          MOV      R0, #074H
    0BA6:    F4 25          CALL     00725H
    0BA8:    B6 B0          JF0      000B0H
    0BAA:    B8 27          MOV      R0, #027H
    0BAC:    10             INC      @R0
    0BAD:    18             INC      R0
    0BAE:    FE             MOV      A, R6
    0BAF:    A0             MOV      @R0, A
    0BB0:    B8 27          MOV      R0, #027H
    0BB2:    F0             MOV      A, @R0
    0BB3:    C6 CB          JZ       000CBH
    0BB5:    FD             MOV      A, R5
    0BB6:    C6 CB          JZ       000CBH
    0BB8:    B0 00          MOV      @R0, #000H
    0BBA:    18             INC      R0
    0BBB:    F0             MOV      A, @R0
    0BBC:    18             INC      R0
    0BBD:    60             ADD      A, @R0
    0BBE:    AA             MOV      R2, A
    0BBF:    6A             ADD      A, R2
    0BC0:    AA             MOV      R2, A
    0BC1:    B8 00          MOV      R0, #000H
    0BC3:    17             INC      A
    0BC4:    B4 10          CALL     00510H
    0BC6:    90             MOVX     @R0, A
    0BC7:    FA             MOV      A, R2
    0BC8:    B4 10          CALL     00510H
    0BCA:    90             MOVX     @R0, A
    0BCB:    24 F4          JMP      001F4H
    0BCD:    27             CLR      A
    0BCE:    B9 72          MOV      R1, #072H
    0BD0:    91             MOVX     @R1, A
    0BD1:    FD             MOV      A, R5
    0BD2:    C6 DB          JZ       000DBH
    0BD4:    27             CLR      A
    0BD5:    B9 18          MOV      R1, #018H
    0BD7:    91             MOVX     @R1, A
    0BD8:    B9 04          MOV      R1, #004H
    0BDA:    91             MOVX     @R1, A
    0BDB:    24 F8          JMP      001F8H
    0BDD:    E5             SEL      MB0
    0BDE:    B9 18          MOV      R1, #018H
    0BE0:    BD 02          MOV      R5, #002H
    0BE2:    F4 AC          CALL     007ACH
    0BE4:    F6 E9          JC       000E9H
    0BE6:    BD 00          MOV      R5, #000H
    0BE8:    83             RET      
    0BE9:    C6 FD          JZ       000FDH
    0BEB:    FD             MOV      A, R5
    0BEC:    91             MOVX     @R1, A
    0BED:    B9 27          MOV      R1, #027H
    0BEF:    11             INC      @R1
    0BF0:    B9 7A          MOV      R1, #07AH
    0BF2:    81             MOVX     A, @R1
    0BF3:    B4 12          CALL     00512H
    0BF5:    B9 04          MOV      R1, #004H
    0BF7:    91             MOVX     @R1, A
    0BF8:    23 37          MOV      A, #037H
    0BFA:    B9 02          MOV      R1, #002H
    0BFC:    91             MOVX     @R1, A
    0BFD:    F5             SEL      MB1
    0BFE:    83             RET      
    0BFF:    8C             ORLD     P4, A
    0C00:    B8 83          MOV      R0, #083H
    0C02:    80             MOVX     A, @R0
    0C03:    C6 DA          JZ       000DAH
    0C05:    B8 84          MOV      R0, #084H
    0C07:    BA BB          MOV      R2, #0BBH
    0C09:    BB 06          MOV      R3, #006H
    0C0B:    23 01          MOV      A, #001H
    0C0D:    90             MOVX     @R0, A
    0C0E:    18             INC      R0
    0C0F:    90             MOVX     @R0, A
    0C10:    18             INC      R0
    0C11:    FA             MOV      A, R2
    0C12:    90             MOVX     @R0, A
    0C13:    18             INC      R0
    0C14:    18             INC      R0
    0C15:    EB 0B          DJNZ     R3, 0000BH
    0C17:    76 32          JF1      00032H
    0C19:    B8 83          MOV      R0, #083H
    0C1B:    80             MOVX     A, @R0
    0C1C:    96 93          JNZ      00093H
    0C1E:    17             INC      A
    0C1F:    90             MOVX     @R0, A
    0C20:    B8 07          MOV      R0, #007H
    0C22:    90             MOVX     @R0, A
    0C23:    23 08          MOV      A, #008H
    0C25:    B8 18          MOV      R0, #018H
    0C27:    90             MOVX     @R0, A
    0C28:    BA BC          MOV      R2, #0BCH
    0C2A:    B8 84          MOV      R0, #084H
    0C2C:    BB 06          MOV      R3, #006H
    0C2E:    F4 99          CALL     00799H
    0C30:    EB 2E          DJNZ     R3, 0002EH
    0C32:    34 FC          CALL     001FCH
    0C34:    B8 85          MOV      R0, #085H
    0C36:    BA FF          MOV      R2, #0FFH
    0C38:    BC 00          MOV      R4, #000H
    0C3A:    BF 06          MOV      R7, #006H
    0C3C:    F4 25          CALL     00725H
    0C3E:    E6 41          JNC      00041H
    0C40:    1C             INC      R4
    0C41:    FF             MOV      A, R7
    0C42:    12 5F          JB0      0005FH
    0C44:    1A             INC      R2
    0C45:    1A             INC      R2
    0C46:    1A             INC      R2
    0C47:    1A             INC      R2
    0C48:    1A             INC      R2
    0C49:    B6 88          JF0      00088H
    0C4B:    FA             MOV      A, R2
    0C4C:    A9             MOV      R1, A
    0C4D:    FF             MOV      A, R7
    0C4E:    D3 06          XRL      A, #006H
    0C50:    96 55          JNZ      00055H
    0C52:    FE             MOV      A, R6
    0C53:    C6 CC          JZ       000CCH
    0C55:    FE             MOV      A, R6
    0C56:    F2 5C          JB7      0005CH
    0C58:    B4 12          CALL     00512H
    0C5A:    76 87          JF1      00087H
    0C5C:    27             CLR      A
    0C5D:    76 87          JF1      00087H
    0C5F:    CA             DEC      R2
    0C60:    CA             DEC      R2
    0C61:    CA             DEC      R2
    0C62:    CA             DEC      R2
    0C63:    FA             MOV      A, R2
    0C64:    A9             MOV      R1, A
    0C65:    FF             MOV      A, R7
    0C66:    52 6E          JB2      0006EH
    0C68:    B6 88          JF0      00088H
    0C6A:    32 84          JB1      00084H
    0C6C:    76 86          JF1      00086H
    0C6E:    18             INC      R0
    0C6F:    18             INC      R0
    0C70:    80             MOVX     A, @R0
    0C71:    C8             DEC      R0
    0C72:    C8             DEC      R0
    0C73:    AE             MOV      R6, A
    0C74:    42             MOV      A, T
    0C75:    53 07          ANL      A, #007H
    0C77:    6E             ADD      A, R6
    0C78:    AE             MOV      R6, A
    0C79:    6E             ADD      A, R6
    0C7A:    AE             MOV      R6, A
    0C7B:    17             INC      A
    0C7C:    B4 10          CALL     00510H
    0C7E:    91             MOVX     @R1, A
    0C7F:    FE             MOV      A, R6
    0C80:    B4 10          CALL     00510H
    0C82:    76 87          JF1      00087H
    0C84:    27             CLR      A
    0C85:    91             MOVX     @R1, A
    0C86:    FE             MOV      A, R6
    0C87:    91             MOVX     @R1, A
    0C88:    18             INC      R0
    0C89:    18             INC      R0
    0C8A:    18             INC      R0
    0C8B:    18             INC      R0
    0C8C:    EF 3C          DJNZ     R7, 0003CH
    0C8E:    FC             MOV      A, R4
    0C8F:    96 93          JNZ      00093H
    0C91:    24 F4          JMP      001F4H
    0C93:    B8 01          MOV      R0, #001H
    0C95:    23 00          MOV      A, #000H
    0C97:    90             MOVX     @R0, A
    0C98:    23 50          MOV      A, #050H
    0C9A:    90             MOVX     @R0, A
    0C9B:    18             INC      R0
    0C9C:    23 12          MOV      A, #012H
    0C9E:    90             MOVX     @R0, A
    0C9F:    18             INC      R0
    0CA0:    18             INC      R0
    0CA1:    23 09          MOV      A, #009H
    0CA3:    B4 12          CALL     00512H
    0CA5:    90             MOVX     @R0, A
    0CA6:    18             INC      R0
    0CA7:    23 07          MOV      A, #007H
    0CA9:    B4 12          CALL     00512H
    0CAB:    90             MOVX     @R0, A
    0CAC:    18             INC      R0
    0CAD:    23 05          MOV      A, #005H
    0CAF:    B4 12          CALL     00512H
    0CB1:    90             MOVX     @R0, A
    0CB2:    34 FC          CALL     001FCH
    0CB4:    B8 00          MOV      R0, #000H
    0CB6:    42             MOV      A, T
    0CB7:    A9             MOV      R1, A
    0CB8:    F1             MOV      A, @R1
    0CB9:    D9             XRL      A, R1
    0CBA:    62             MOV      T, A
    0CBB:    53 07          ANL      A, #007H
    0CBD:    03 14          ADD      A, #014H
    0CBF:    AE             MOV      R6, A
    0CC0:    6E             ADD      A, R6
    0CC1:    AE             MOV      R6, A
    0CC2:    17             INC      A
    0CC3:    B4 10          CALL     00510H
    0CC5:    90             MOVX     @R0, A
    0CC6:    FE             MOV      A, R6
    0CC7:    B4 10          CALL     00510H
    0CC9:    90             MOVX     @R0, A
    0CCA:    24 F4          JMP      001F4H
    0CCC:    B8 04          MOV      R0, #004H
    0CCE:    27             CLR      A
    0CCF:    90             MOVX     @R0, A
    0CD0:    18             INC      R0
    0CD1:    90             MOVX     @R0, A
    0CD2:    18             INC      R0
    0CD3:    90             MOVX     @R0, A
    0CD4:    B8 18          MOV      R0, #018H
    0CD6:    90             MOVX     @R0, A
    0CD7:    B8 83          MOV      R0, #083H
    0CD9:    90             MOVX     @R0, A
    0CDA:    24 F8          JMP      001F8H
    0CDC:    C8             DEC      R0
    0CDD:    8C             ORLD     P4, A
    0CDE:    C8             DEC      R0
    0CDF:    8C             ORLD     P4, A
    0CE0:    C8             DEC      R0
    0CE1:    8C             ORLD     P4, A
    0CE2:    C8             DEC      R0
    0CE3:    8C             ORLD     P4, A
    0CE4:    C8             DEC      R0
    0CE5:    8C             ORLD     P4, A
    0CE6:    C8             DEC      R0
    0CE7:    8C             ORLD     P4, A
    0CE8:    C8             DEC      R0
    0CE9:    8C             ORLD     P4, A
    0CEA:    C8             DEC      R0
    0CEB:    8C             ORLD     P4, A
    0CEC:    C8             DEC      R0
    0CED:    8C             ORLD     P4, A
    0CEE:    C8             DEC      R0
    0CEF:    8C             ORLD     P4, A
    0CF0:    C8             DEC      R0
    0CF1:    8C             ORLD     P4, A
    0CF2:    C8             DEC      R0
    0CF3:    8C             ORLD     P4, A
    0CF4:    C8             DEC      R0
    0CF5:    8C             ORLD     P4, A
    0CF6:    C8             DEC      R0
    0CF7:    8C             ORLD     P4, A
    0CF8:    C8             DEC      R0
    0CF9:    8C             ORLD     P4, A
    0CFA:    C8             DEC      R0
    0CFB:    8C             ORLD     P4, A
    0CFC:    C8             DEC      R0
    0CFD:    8C             ORLD     P4, A
    0CFE:    C8             DEC      R0
    0CFF:    8C             ORLD     P4, A
    0D00:    B8 2D          MOV      R0, #02DH
    0D02:    B0 01          MOV      @R0, #001H
    0D04:    18             INC      R0
    0D05:    B0 0F          MOV      @R0, #00FH
    0D07:    B8 07          MOV      R0, #007H
    0D09:    23 01          MOV      A, #001H
    0D0B:    90             MOVX     @R0, A
    0D0C:    34 FC          CALL     001FCH
    0D0E:    B9 18          MOV      R1, #018H
    0D10:    BD 04          MOV      R5, #004H
    0D12:    F4 AC          CALL     007ACH
    0D14:    F6 1A          JC       0001AH
    0D16:    BD 00          MOV      R5, #000H
    0D18:    76 1E          JF1      0001EH
    0D1A:    C6 1E          JZ       0001EH
    0D1C:    FD             MOV      A, R5
    0D1D:    91             MOVX     @R1, A
    0D1E:    B8 2D          MOV      R0, #02DH
    0D20:    F0             MOV      A, @R0
    0D21:    07             DEC      A
    0D22:    96 2D          JNZ      0002DH
    0D24:    18             INC      R0
    0D25:    F0             MOV      A, @R0
    0D26:    07             DEC      A
    0D27:    C6 56          JZ       00056H
    0D29:    A0             MOV      @R0, A
    0D2A:    C8             DEC      R0
    0D2B:    23 2F          MOV      A, #02FH
    0D2D:    A0             MOV      @R0, A
    0D2E:    18             INC      R0
    0D2F:    FD             MOV      A, R5
    0D30:    C6 54          JZ       00054H
    0D32:    B9 02          MOV      R1, #002H
    0D34:    23 32          MOV      A, #032H
    0D36:    91             MOVX     @R1, A
    0D37:    F0             MOV      A, @R0
    0D38:    B4 12          CALL     00512H
    0D3A:    B8 04          MOV      R0, #004H
    0D3C:    90             MOVX     @R0, A
    0D3D:    18             INC      R0
    0D3E:    90             MOVX     @R0, A
    0D3F:    B8 00          MOV      R0, #000H
    0D41:    23 5F          MOV      A, #05FH
    0D43:    90             MOVX     @R0, A
    0D44:    42             MOV      A, T
    0D45:    53 01          ANL      A, #001H
    0D47:    03 3B          ADD      A, #03BH
    0D49:    90             MOVX     @R0, A
    0D4A:    18             INC      R0
    0D4B:    23 9F          MOV      A, #09FH
    0D4D:    90             MOVX     @R0, A
    0D4E:    42             MOV      A, T
    0D4F:    53 01          ANL      A, #001H
    0D51:    03 28          ADD      A, #028H
    0D53:    90             MOVX     @R0, A
    0D54:    24 F4          JMP      001F4H
    0D56:    FD             MOV      A, R5
    0D57:    C6 62          JZ       00062H
    0D59:    27             CLR      A
    0D5A:    B8 04          MOV      R0, #004H
    0D5C:    90             MOVX     @R0, A
    0D5D:    18             INC      R0
    0D5E:    90             MOVX     @R0, A
    0D5F:    B8 18          MOV      R0, #018H
    0D61:    90             MOVX     @R0, A
    0D62:    24 F8          JMP      001F8H
    0D64:    B8 9C          MOV      R0, #09CH
    0D66:    80             MOVX     A, @R0
    0D67:    12 6B          JB0      0006BH
    0D69:    24 FA          JMP      001FAH
    0D6B:    43 80          ORL      A, #080H
    0D6D:    90             MOVX     @R0, A
    0D6E:    24 FA          JMP      001FAH
    0D70:    23 54          MOV      A, #054H
    0D72:    BB FF          MOV      R3, #0FFH
    0D74:    76 7A          JF1      0007AH
    0D76:    23 E6          MOV      A, #0E6H
    0D78:    BB FB          MOV      R3, #0FBH
    0D7A:    B8 2F          MOV      R0, #02FH
    0D7C:    A0             MOV      @R0, A
    0D7D:    18             INC      R0
    0D7E:    B0 FF          MOV      @R0, #0FFH
    0D80:    18             INC      R0
    0D81:    FB             MOV      A, R3
    0D82:    A0             MOV      @R0, A
    0D83:    18             INC      R0
    0D84:    B0 E8          MOV      @R0, #0E8H
    0D86:    18             INC      R0
    0D87:    B0 03          MOV      @R0, #003H
    0D89:    B8 9C          MOV      R0, #09CH
    0D8B:    80             MOVX     A, @R0
    0D8C:    43 01          ORL      A, #001H
    0D8E:    90             MOVX     @R0, A
    0D8F:    34 FC          CALL     001FCH
    0D91:    B8 9C          MOV      R0, #09CH
    0D93:    80             MOVX     A, @R0
    0D94:    F2 D7          JB7      000D7H
    0D96:    B9 1D          MOV      R1, #01DH
    0D98:    BD 07          MOV      R5, #007H
    0D9A:    F4 AC          CALL     007ACH
    0D9C:    85             CLR      F0
    0D9D:    B8 11          MOV      R0, #011H
    0D9F:    F6 A4          JC       000A4H
    0DA1:    95             CPL      F0
    0DA2:    76 B4          JF1      000B4H
    0DA4:    C6 B4          JZ       000B4H
    0DA6:    FD             MOV      A, R5
    0DA7:    91             MOVX     @R1, A
    0DA8:    B9 32          MOV      R1, #032H
    0DAA:    F1             MOV      A, @R1
    0DAB:    90             MOVX     @R0, A
    0DAC:    19             INC      R1
    0DAD:    F1             MOV      A, @R1
    0DAE:    90             MOVX     @R0, A
    0DAF:    B9 15          MOV      R1, #015H
    0DB1:    23 81          MOV      A, #081H
    0DB3:    91             MOVX     @R1, A
    0DB4:    B9 2F          MOV      R1, #02FH
    0DB6:    F1             MOV      A, @R1
    0DB7:    19             INC      R1
    0DB8:    61             ADD      A, @R1
    0DB9:    A1             MOV      @R1, A
    0DBA:    E6 D5          JNC      000D5H
    0DBC:    19             INC      R1
    0DBD:    F1             MOV      A, @R1
    0DBE:    19             INC      R1
    0DBF:    61             ADD      A, @R1
    0DC0:    A1             MOV      @R1, A
    0DC1:    AA             MOV      R2, A
    0DC2:    19             INC      R1
    0DC3:    F1             MOV      A, @R1
    0DC4:    F6 C8          JC       000C8H
    0DC6:    07             DEC      A
    0DC7:    A1             MOV      @R1, A
    0DC8:    96 CF          JNZ      000CFH
    0DCA:    FA             MOV      A, R2
    0DCB:    D3 14          XRL      A, #014H
    0DCD:    C6 D7          JZ       000D7H
    0DCF:    B6 D5          JF0      000D5H
    0DD1:    FA             MOV      A, R2
    0DD2:    90             MOVX     @R0, A
    0DD3:    F1             MOV      A, @R1
    0DD4:    90             MOVX     @R0, A
    0DD5:    24 F4          JMP      001F4H
    0DD7:    B9 1D          MOV      R1, #01DH
    0DD9:    BD 07          MOV      R5, #007H
    0DDB:    F4 AC          CALL     007ACH
    0DDD:    E6 E5          JNC      000E5H
    0DDF:    96 E5          JNZ      000E5H
    0DE1:    91             MOVX     @R1, A
    0DE2:    B8 15          MOV      R0, #015H
    0DE4:    90             MOVX     @R0, A
    0DE5:    B8 9C          MOV      R0, #09CH
    0DE7:    27             CLR      A
    0DE8:    90             MOVX     @R0, A
    0DE9:    24 F8          JMP      001F8H
    0DEB:    8C             ORLD     P4, A
    0DEC:    C8             DEC      R0
    0DED:    8C             ORLD     P4, A
    0DEE:    C8             DEC      R0
    0DEF:    8C             ORLD     P4, A
    0DF0:    C8             DEC      R0
    0DF1:    8C             ORLD     P4, A
    0DF2:    C8             DEC      R0
    0DF3:    8C             ORLD     P4, A
    0DF4:    C8             DEC      R0
    0DF5:    8C             ORLD     P4, A
    0DF6:    C8             DEC      R0
    0DF7:    8C             ORLD     P4, A
    0DF8:    C8             DEC      R0
    0DF9:    8C             ORLD     P4, A
    0DFA:    C8             DEC      R0
    0DFB:    8C             ORLD     P4, A
    0DFC:    C8             DEC      R0
    0DFD:    8C             ORLD     P4, A
    0DFE:    C8             DEC      R0
    0DFF:    8C             ORLD     P4, A
    0E00:    D8             XRL      A, R0
    0E01:    00             NOP      
    0E02:    EA 3C          DJNZ     R2, 0003CH
    0E04:    D8             XRL      A, R0
    0E05:    02             OUTL     BUS, A
    0E06:    EA 2C          DJNZ     R2, 0002CH
    0E08:    B8 AD          MOV      R0, #0ADH
    0E0A:    80             MOVX     A, @R0
    0E0B:    12 0F          JB0      0000FH
    0E0D:    24 FA          JMP      001FAH
    0E0F:    43 80          ORL      A, #080H
    0E11:    90             MOVX     @R0, A
    0E12:    24 FA          JMP      001FAH
    0E14:    23 90          MOV      A, #090H
    0E16:    BA 00          MOV      R2, #000H
    0E18:    76 1E          JF1      0001EH
    0E1A:    23 50          MOV      A, #050H
    0E1C:    BA 04          MOV      R2, #004H
    0E1E:    B9 38          MOV      R1, #038H
    0E20:    A1             MOV      @R1, A
    0E21:    19             INC      R1
    0E22:    B1 FF          MOV      @R1, #0FFH
    0E24:    B8 AE          MOV      R0, #0AEH
    0E26:    F5             SEL      MB1
    0E27:    D4 E7          CALL     006E7H
    0E29:    B8 AD          MOV      R0, #0ADH
    0E2B:    80             MOVX     A, @R0
    0E2C:    43 01          ORL      A, #001H
    0E2E:    90             MOVX     @R0, A
    0E2F:    34 FC          CALL     001FCH
    0E31:    B8 AD          MOV      R0, #0ADH
    0E33:    80             MOVX     A, @R0
    0E34:    BF 38          MOV      R7, #038H
    0E36:    BD 08          MOV      R5, #008H
    0E38:    F2 3E          JB7      0003EH
    0E3A:    B8 AF          MOV      R0, #0AFH
    0E3C:    76 7A          JF1      0007AH
    0E3E:    27             CLR      A
    0E3F:    90             MOVX     @R0, A
    0E40:    B9 1D          MOV      R1, #01DH
    0E42:    F4 AC          CALL     007ACH
    0E44:    E6 E5          JNC      000E5H
    0E46:    96 E5          JNZ      000E5H
    0E48:    76 DB          JF1      000DBH
    0E4A:    B8 9D          MOV      R0, #09DH
    0E4C:    BA F4          MOV      R2, #0F4H
    0E4E:    F4 99          CALL     00799H
    0E50:    F4 99          CALL     00799H
    0E52:    B9 34          MOV      R1, #034H
    0E54:    B1 19          MOV      @R1, #019H
    0E56:    19             INC      R1
    0E57:    B1 FF          MOV      @R1, #0FFH
    0E59:    34 FC          CALL     001FCH
    0E5B:    B8 9E          MOV      R0, #09EH
    0E5D:    BF 34          MOV      R7, #034H
    0E5F:    BD 09          MOV      R5, #009H
    0E61:    76 7A          JF1      0007AH
    0E63:    B8 A5          MOV      R0, #0A5H
    0E65:    BA F8          MOV      R2, #0F8H
    0E67:    F4 99          CALL     00799H
    0E69:    F4 99          CALL     00799H
    0E6B:    B9 36          MOV      R1, #036H
    0E6D:    B1 DC          MOV      @R1, #0DCH
    0E6F:    19             INC      R1
    0E70:    B1 FF          MOV      @R1, #0FFH
    0E72:    34 FC          CALL     001FCH
    0E74:    B8 A6          MOV      R0, #0A6H
    0E76:    BF 36          MOV      R7, #036H
    0E78:    BD 06          MOV      R5, #006H
    0E7A:    B9 1D          MOV      R1, #01DH
    0E7C:    F4 AC          CALL     007ACH
    0E7E:    F6 84          JC       00084H
    0E80:    BD 00          MOV      R5, #000H
    0E82:    76 A8          JF1      000A8H
    0E84:    C6 A8          JZ       000A8H
    0E86:    FD             MOV      A, R5
    0E87:    91             MOVX     @R1, A
    0E88:    B9 15          MOV      R1, #015H
    0E8A:    18             INC      R0
    0E8B:    18             INC      R0
    0E8C:    80             MOVX     A, @R0
    0E8D:    F2 DB          JB7      000DBH
    0E8F:    B4 12          CALL     00512H
    0E91:    91             MOVX     @R1, A
    0E92:    18             INC      R0
    0E93:    18             INC      R0
    0E94:    18             INC      R0
    0E95:    18             INC      R0
    0E96:    B9 11          MOV      R1, #011H
    0E98:    80             MOVX     A, @R0
    0E99:    AE             MOV      R6, A
    0E9A:    6E             ADD      A, R6
    0E9B:    AE             MOV      R6, A
    0E9C:    17             INC      A
    0E9D:    B4 10          CALL     00510H
    0E9F:    91             MOVX     @R1, A
    0EA0:    FE             MOV      A, R6
    0EA1:    B4 10          CALL     00510H
    0EA3:    91             MOVX     @R1, A
    0EA4:    F8             MOV      A, R0
    0EA5:    03 FA          ADD      A, #0FAH
    0EA7:    A8             MOV      R0, A
    0EA8:    FF             MOV      A, R7
    0EA9:    A9             MOV      R1, A
    0EAA:    F1             MOV      A, @R1
    0EAB:    19             INC      R1
    0EAC:    61             ADD      A, @R1
    0EAD:    A1             MOV      @R1, A
    0EAE:    E6 D9          JNC      000D9H
    0EB0:    F4 5D          CALL     0075DH
    0EB2:    F6 DB          JC       000DBH
    0EB4:    B6 C1          JF0      000C1H
    0EB6:    FD             MOV      A, R5
    0EB7:    C6 C1          JZ       000C1H
    0EB9:    FE             MOV      A, R6
    0EBA:    F2 DB          JB7      000DBH
    0EBC:    B4 12          CALL     00512H
    0EBE:    B9 15          MOV      R1, #015H
    0EC0:    91             MOVX     @R1, A
    0EC1:    18             INC      R0
    0EC2:    18             INC      R0
    0EC3:    18             INC      R0
    0EC4:    18             INC      R0
    0EC5:    F4 5D          CALL     0075DH
    0EC7:    B6 D9          JF0      000D9H
    0EC9:    FD             MOV      A, R5
    0ECA:    C6 D9          JZ       000D9H
    0ECC:    B9 11          MOV      R1, #011H
    0ECE:    FE             MOV      A, R6
    0ECF:    6E             ADD      A, R6
    0ED0:    AE             MOV      R6, A
    0ED1:    17             INC      A
    0ED2:    B4 10          CALL     00510H
    0ED4:    91             MOVX     @R1, A
    0ED5:    FE             MOV      A, R6
    0ED6:    B4 10          CALL     00510H
    0ED8:    91             MOVX     @R1, A
    0ED9:    24 F4          JMP      001F4H
    0EDB:    FD             MOV      A, R5
    0EDC:    C6 E5          JZ       000E5H
    0EDE:    27             CLR      A
    0EDF:    B8 15          MOV      R0, #015H
    0EE1:    90             MOVX     @R0, A
    0EE2:    B8 1D          MOV      R0, #01DH
    0EE4:    90             MOVX     @R0, A
    0EE5:    24 F8          JMP      001F8H
    0EE7:    BB 02          MOV      R3, #002H
    0EE9:    23 01          MOV      A, #001H
    0EEB:    90             MOVX     @R0, A
    0EEC:    18             INC      R0
    0EED:    90             MOVX     @R0, A
    0EEE:    18             INC      R0
    0EEF:    FA             MOV      A, R2
    0EF0:    1A             INC      R2
    0EF1:    A3             MOVP     A, @A
    0EF2:    90             MOVX     @R0, A
    0EF3:    18             INC      R0
    0EF4:    FA             MOV      A, R2
    0EF5:    1A             INC      R2
    0EF6:    A3             MOVP     A, @A
    0EF7:    90             MOVX     @R0, A
    0EF8:    18             INC      R0
    0EF9:    EB E9          DJNZ     R3, 000E9H
    0EFB:    E5             SEL      MB0
    0EFC:    83             RET      
    0EFD:    8C             ORLD     P4, A
    0EFE:    C8             DEC      R0
    0EFF:    8C             ORLD     P4, A
    0F00:    C8             DEC      R0
    0F01:    8C             ORLD     P4, A
    0F02:    C8             DEC      R0
    0F03:    8C             ORLD     P4, A
    0F04:    C8             DEC      R0
    0F05:    8C             ORLD     P4, A
    0F06:    C8             DEC      R0
    0F07:    8C             ORLD     P4, A
    0F08:    C8             DEC      R0
    0F09:    8C             ORLD     P4, A
    0F0A:    C8             DEC      R0
    0F0B:    8C             ORLD     P4, A
    0F0C:    C8             DEC      R0
    0F0D:    8C             ORLD     P4, A
    0F0E:    C8             DEC      R0
    0F0F:    8C             ORLD     P4, A
    0F10:    C8             DEC      R0
    0F11:    8C             ORLD     P4, A
    0F12:    C8             DEC      R0
    0F13:    8C             ORLD     P4, A
    0F14:    C8             DEC      R0
    0F15:    8C             ORLD     P4, A
    0F16:    C8             DEC      R0
    0F17:    8C             ORLD     P4, A
    0F18:    C8             DEC      R0
    0F19:    8C             ORLD     P4, A
    0F1A:    C8             DEC      R0
    0F1B:    8C             ORLD     P4, A
    0F1C:    C8             DEC      R0
    0F1D:    8C             ORLD     P4, A
    0F1E:    C8             DEC      R0
    0F1F:    8C             ORLD     P4, A
    0F20:    C8             DEC      R0
    0F21:    06             ???      
    0F22:    01             ???      
    0F23:    8C             ORLD     P4, A
    0F24:    C8             DEC      R0
    0F25:    8C             ORLD     P4, A
    0F26:    C8             DEC      R0
    0F27:    8C             ORLD     P4, A
    0F28:    C8             DEC      R0
    0F29:    8C             ORLD     P4, A
    0F2A:    C8             DEC      R0
    0F2B:    8C             ORLD     P4, A
    0F2C:    C8             DEC      R0
    0F2D:    8C             ORLD     P4, A
    0F2E:    C8             DEC      R0
    0F2F:    8C             ORLD     P4, A
    0F30:    C8             DEC      R0
    0F31:    8C             ORLD     P4, A
    0F32:    C8             DEC      R0
    0F33:    8C             ORLD     P4, A
    0F34:    C8             DEC      R0
    0F35:    8C             ORLD     P4, A
    0F36:    C8             DEC      R0
    0F37:    8C             ORLD     P4, A
    0F38:    C8             DEC      R0
    0F39:    8C             ORLD     P4, A
    0F3A:    C8             DEC      R0
    0F3B:    8C             ORLD     P4, A
    0F3C:    C8             DEC      R0
    0F3D:    8C             ORLD     P4, A
    0F3E:    C8             DEC      R0
    0F3F:    8C             ORLD     P4, A
    0F40:    C8             DEC      R0
    0F41:    8C             ORLD     P4, A
    0F42:    C8             DEC      R0
    0F43:    8C             ORLD     P4, A
    0F44:    C8             DEC      R0
    0F45:    8C             ORLD     P4, A
    0F46:    C8             DEC      R0
    0F47:    8C             ORLD     P4, A
    0F48:    C8             DEC      R0
    0F49:    8C             ORLD     P4, A
    0F4A:    C8             DEC      R0
    0F4B:    8C             ORLD     P4, A
    0F4C:    C8             DEC      R0
    0F4D:    8C             ORLD     P4, A
    0F4E:    C8             DEC      R0
    0F4F:    8C             ORLD     P4, A
    0F50:    C8             DEC      R0
    0F51:    8C             ORLD     P4, A
    0F52:    C8             DEC      R0
    0F53:    8C             ORLD     P4, A
    0F54:    C8             DEC      R0
    0F55:    8C             ORLD     P4, A
    0F56:    C8             DEC      R0
    0F57:    8C             ORLD     P4, A
    0F58:    C8             DEC      R0
    0F59:    8C             ORLD     P4, A
    0F5A:    C8             DEC      R0
    0F5B:    8C             ORLD     P4, A
    0F5C:    C8             DEC      R0
    0F5D:    8C             ORLD     P4, A
    0F5E:    C8             DEC      R0
    0F5F:    8C             ORLD     P4, A
    0F60:    C8             DEC      R0
    0F61:    8C             ORLD     P4, A
    0F62:    C8             DEC      R0
    0F63:    8C             ORLD     P4, A
    0F64:    C8             DEC      R0
    0F65:    8C             ORLD     P4, A
    0F66:    C8             DEC      R0
    0F67:    8C             ORLD     P4, A
    0F68:    C8             DEC      R0
    0F69:    8C             ORLD     P4, A
    0F6A:    C8             DEC      R0
    0F6B:    8C             ORLD     P4, A
    0F6C:    C8             DEC      R0
    0F6D:    8C             ORLD     P4, A
    0F6E:    C8             DEC      R0
    0F6F:    8C             ORLD     P4, A
    0F70:    C8             DEC      R0
    0F71:    8C             ORLD     P4, A
    0F72:    C8             DEC      R0
    0F73:    8C             ORLD     P4, A
    0F74:    C8             DEC      R0
    0F75:    8C             ORLD     P4, A
    0F76:    C8             DEC      R0
    0F77:    8C             ORLD     P4, A
    0F78:    C8             DEC      R0
    0F79:    8C             ORLD     P4, A
    0F7A:    C8             DEC      R0
    0F7B:    8C             ORLD     P4, A
    0F7C:    C8             DEC      R0
    0F7D:    8C             ORLD     P4, A
    0F7E:    C8             DEC      R0
    0F7F:    8C             ORLD     P4, A
    0F80:    F5             SEL      MB1
    0F81:    F4 E3          CALL     007E3H
    0F83:    D2 88          JB6      00088H
    0F85:    E5             SEL      MB0
    0F86:    24 FA          JMP      001FAH
    0F88:    AF             MOV      R7, A
    0F89:    53 03          ANL      A, #003H
    0F8B:    AE             MOV      R6, A
    0F8C:    F4 D4          CALL     007D4H
    0F8E:    A8             MOV      R0, A
    0F8F:    F4 D4          CALL     007D4H
    0F91:    AD             MOV      R5, A
    0F92:    85             CLR      F0
    0F93:    FF             MOV      A, R7
    0F94:    52 9C          JB2      0009CH
    0F96:    95             CPL      F0
    0F97:    FE             MOV      A, R6
    0F98:    43 40          ORL      A, #040H
    0F9A:    3A             OUTL     P2, A
    0F9B:    FF             MOV      A, R7
    0F9C:    B2 B2          JB5      000B2H
    0F9E:    B6 A3          JF0      000A3H
    0FA0:    F0             MOV      A, @R0
    0FA1:    E4 A4          JMP      007A4H
    0FA3:    80             MOVX     A, @R0
    0FA4:    18             INC      R0
    0FA5:    F4 C1          CALL     007C1H
    0FA7:    ED 9E          DJNZ     R5, 0009EH
    0FA9:    F4 BB          CALL     007BBH
    0FAB:    27             CLR      A
    0FAC:    3A             OUTL     P2, A
    0FAD:    43 40          ORL      A, #040H
    0FAF:    3A             OUTL     P2, A
    0FB0:    E4 81          JMP      00781H
    0FB2:    FD             MOV      A, R5
    0FB3:    B6 B8          JF0      000B8H
    0FB5:    A0             MOV      @R0, A
    0FB6:    E4 B9          JMP      007B9H
    0FB8:    90             MOVX     @R0, A
    0FB9:    E4 81          JMP      00781H
    0FBB:    09             IN       A, P1
    0FBC:    53 7F          ANL      A, #07FH
    0FBE:    C6 BB          JZ       000BBH
    0FC0:    83             RET      
    0FC1:    B9 08          MOV      R1, #008H
    0FC3:    AC             MOV      R4, A
    0FC4:    F4 BB          CALL     007BBH
    0FC6:    FC             MOV      A, R4
    0FC7:    77             RR       A
    0FC8:    AC             MOV      R4, A
    0FC9:    43 7F          ORL      A, #07FH
    0FCB:    39             OUTL     P1, A
    0FCC:    FE             MOV      A, R6
    0FCD:    3A             OUTL     P2, A
    0FCE:    43 40          ORL      A, #040H
    0FD0:    3A             OUTL     P2, A
    0FD1:    E9 C4          DJNZ     R1, 000C4H
    0FD3:    83             RET      
    0FD4:    F4 E3          CALL     007E3H
    0FD6:    53 0F          ANL      A, #00FH
    0FD8:    AD             MOV      R5, A
    0FD9:    F4 E3          CALL     007E3H
    0FDB:    53 0F          ANL      A, #00FH
    0FDD:    E7             RL       A
    0FDE:    E7             RL       A
    0FDF:    E7             RL       A
    0FE0:    E7             RL       A
    0FE1:    4D             ORL      A, R5
    0FE2:    83             RET      
    0FE3:    F4 BB          CALL     007BBH
    0FE5:    AA             MOV      R2, A
    0FE6:    09             IN       A, P1
    0FE7:    53 7F          ANL      A, #07FH
    0FE9:    AB             MOV      R3, A
    0FEA:    DA             XRL      A, R2
    0FEB:    C6 F0          JZ       000F0H
    0FED:    FB             MOV      A, R3
    0FEE:    E4 E5          JMP      007E5H
    0FF0:    3A             OUTL     P2, A
    0FF1:    23 40          MOV      A, #040H
    0FF3:    3A             OUTL     P2, A
    0FF4:    FA             MOV      A, R2
    0FF5:    83             RET      
    0FF6:    C8             DEC      R0
    0FF7:    8C             ORLD     P4, A
    0FF8:    C8             DEC      R0
    0FF9:    8C             ORLD     P4, A
    0FFA:    C8             DEC      R0
    0FFB:    8C             ORLD     P4, A
    0FFC:    C8             DEC      R0
    0FFD:    8C             ORLD     P4, A
    0FFE:    C8             DEC      R0
    0FFF:    8C             ORLD     P4, A

