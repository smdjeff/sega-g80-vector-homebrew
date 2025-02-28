   dasm48 -- Intel MCS-48 (8048, 8049) Disassembler --
-----------------------------------------------------------------

;   Processing "1670.bin" (2048 bytes)
;   Disassembly start address: 0x0000
;   String terminator: 0x00

Start:
    0000:    15             DIS      I
    0001:    27             CLR      A
    0002:    D7             MOV      PSW, A
    0003:    C5             SEL      RB0
    0004:    E5             SEL      MB0
    0005:    94 3B          CALL     0043BH
    0007:    BA 38          MOV      R2, #038H
    0009:    04 0D          JMP      0000DH
    000B:    BA 32          MOV      R2, #032H
    000D:    15             DIS      I
    000E:    C5             SEL      RB0
    000F:    E5             SEL      MB0
    0010:    23 80          MOV      A, #080H
    0012:    3A             OUTL     P2, A
    0013:    27             CLR      A
    0014:    B8 08          MOV      R0, #008H
    0016:    A0             MOV      @R0, A
    0017:    18             INC      R0
    0018:    EA 16          DJNZ     R2, 00016H
    001A:    B8 2D          MOV      R0, #02DH
    001C:    B0 FF          MOV      @R0, #0FFH
    001E:    B8 1B          MOV      R0, #01BH
    0020:    B0 40          MOV      @R0, #040H
    0022:    14 2E          CALL     0002EH
    0024:    B8 1F          MOV      R0, #01FH
    0026:    B0 30          MOV      @R0, #030H
    0028:    B8 1E          MOV      R0, #01EH
    002A:    B0 08          MOV      @R0, #008H
    002C:    44 30          JMP      00230H
    002E:    BB 02          MOV      R3, #002H
    0030:    B8 2A          MOV      R0, #02AH
    0032:    B9 22          MOV      R1, #022H
    0034:    F0             MOV      A, @R0
    0035:    AA             MOV      R2, A
    0036:    F1             MOV      A, @R1
    0037:    A0             MOV      @R0, A
    0038:    FA             MOV      A, R2
    0039:    A1             MOV      @R1, A
    003A:    18             INC      R0
    003B:    19             INC      R1
    003C:    EB 34          DJNZ     R3, 00034H
    003E:    B8 2B          MOV      R0, #02BH
    0040:    B9 2E          MOV      R1, #02EH
    0042:    F0             MOV      A, @R0
    0043:    90             MOVX     @R0, A
    0044:    C8             DEC      R0
    0045:    F0             MOV      A, @R0
    0046:    90             MOVX     @R0, A
    0047:    C8             DEC      R0
    0048:    F1             MOV      A, @R1
    0049:    90             MOVX     @R0, A
    004A:    C9             DEC      R1
    004B:    F0             MOV      A, @R0
    004C:    90             MOVX     @R0, A
    004D:    C8             DEC      R0
    004E:    F0             MOV      A, @R0
    004F:    90             MOVX     @R0, A
    0050:    F1             MOV      A, @R1
    0051:    90             MOVX     @R0, A
    0052:    C8             DEC      R0
    0053:    F0             MOV      A, @R0
    0054:    90             MOVX     @R0, A
    0055:    C8             DEC      R0
    0056:    F0             MOV      A, @R0
    0057:    90             MOVX     @R0, A
    0058:    B9 1B          MOV      R1, #01BH
    005A:    F1             MOV      A, @R1
    005B:    53 7F          ANL      A, #07FH
    005D:    17             INC      A
    005E:    90             MOVX     @R0, A
    005F:    C8             DEC      R0
    0060:    BA 06          MOV      R2, #006H
    0062:    F0             MOV      A, @R0
    0063:    90             MOVX     @R0, A
    0064:    C8             DEC      R0
    0065:    EA 62          DJNZ     R2, 00062H
    0067:    BB 02          MOV      R3, #002H
    0069:    B8 2A          MOV      R0, #02AH
    006B:    B9 22          MOV      R1, #022H
    006D:    F0             MOV      A, @R0
    006E:    AA             MOV      R2, A
    006F:    F1             MOV      A, @R1
    0070:    A0             MOV      @R0, A
    0071:    FA             MOV      A, R2
    0072:    A1             MOV      @R1, A
    0073:    18             INC      R0
    0074:    19             INC      R1
    0075:    EB 6D          DJNZ     R3, 0006DH
    0077:    83             RET      
    0078:    AB             MOV      R3, A
    0079:    84 C0          JMP      004C0H
    007B:    B8 1F          MOV      R0, #01FH
    007D:    F0             MOV      A, @R0
    007E:    A9             MOV      R1, A
    007F:    37             CPL      A
    0080:    03 3A          ADD      A, #03AH
    0082:    37             CPL      A
    0083:    96 87          JNZ      00087H
    0085:    44 2E          JMP      0022EH
    0087:    FB             MOV      A, R3
    0088:    A1             MOV      @R1, A
    0089:    10             INC      @R0
    008A:    19             INC      R1
    008B:    B1 00          MOV      @R1, #000H
    008D:    B8 1D          MOV      R0, #01DH
    008F:    F0             MOV      A, @R0
    0090:    53 FC          ANL      A, #0FCH
    0092:    C6 96          JZ       00096H
    0094:    44 2E          JMP      0022EH
    0096:    B8 30          MOV      R0, #030H
    0098:    F0             MOV      A, @R0
    0099:    C6 0B          JZ       0000BH
    009B:    AB             MOV      R3, A
    009C:    B9 13          MOV      R1, #013H
    009E:    B1 00          MOV      @R1, #000H
    00A0:    19             INC      R1
    00A1:    B1 00          MOV      @R1, #000H
    00A3:    C9             DEC      R1
    00A4:    54 73          CALL     00273H
    00A6:    37             CPL      A
    00A7:    6B             ADD      A, R3
    00A8:    F2 AC          JB7      000ACH
    00AA:    84 5E          JMP      0045EH
    00AC:    FB             MOV      A, R3
    00AD:    6B             ADD      A, R3
    00AE:    A1             MOV      @R1, A
    00AF:    54 73          CALL     00273H
    00B1:    AB             MOV      R3, A
    00B2:    54 73          CALL     00273H
    00B4:    19             INC      R1
    00B5:    A1             MOV      @R1, A
    00B6:    6B             ADD      A, R3
    00B7:    96 BB          JNZ      000BBH
    00B9:    84 5E          JMP      0045EH
    00BB:    FB             MOV      A, R3
    00BC:    C9             DEC      R1
    00BD:    A1             MOV      @R1, A
    00BE:    54 73          CALL     00273H
    00C0:    AB             MOV      R3, A
    00C1:    B8 1D          MOV      R0, #01DH
    00C3:    A0             MOV      @R0, A
    00C4:    54 73          CALL     00273H
    00C6:    C8             DEC      R0
    00C7:    A0             MOV      @R0, A
    00C8:    FB             MOV      A, R3
    00C9:    53 C0          ANL      A, #0C0H
    00CB:    B8 2F          MOV      R0, #02FH
    00CD:    A0             MOV      @R0, A
    00CE:    B8 18          MOV      R0, #018H
    00D0:    D2 D8          JB6      000D8H
    00D2:    23 5E          MOV      A, #05EH
    00D4:    BB 46          MOV      R3, #046H
    00D6:    04 DC          JMP      000DCH
    00D8:    23 6A          MOV      A, #06AH
    00DA:    BB 52          MOV      R3, #052H
    00DC:    A0             MOV      @R0, A
    00DD:    18             INC      R0
    00DE:    FB             MOV      A, R3
    00DF:    A0             MOV      @R0, A
    00E0:    23 C0          MOV      A, #0C0H
    00E2:    54 8B          CALL     0028BH
    00E4:    04 E6          JMP      000E6H
    00E6:    AF             MOV      R7, A
    00E7:    B8 12          MOV      R0, #012H
    00E9:    A0             MOV      @R0, A
    00EA:    53 FC          ANL      A, #0FCH
    00EC:    96 F0          JNZ      000F0H
    00EE:    84 46          JMP      00446H
    00F0:    67             RRC      A
    00F1:    67             RRC      A
    00F2:    53 0F          ANL      A, #00FH
    00F4:    B8 1A          MOV      R0, #01AH
    00F6:    A0             MOV      @R0, A
    00F7:    FF             MOV      A, R7
    00F8:    53 C0          ANL      A, #0C0H
    00FA:    96 FE          JNZ      000FEH
    00FC:    64 FB          JMP      003FBH
    00FE:    F7             RLC      A
    00FF:    F6 09          JC       00009H
    0101:    23 FC          MOV      A, #0FCH
    0103:    54 8B          CALL     0028BH
    0105:    54 BA          CALL     002BAH
    0107:    24 D1          JMP      001D1H
    0109:    F7             RLC      A
    010A:    23 FC          MOV      A, #0FCH
    010C:    F6 18          JC       00018H
    010E:    FF             MOV      A, R7
    010F:    53 03          ANL      A, #003H
    0111:    77             RR       A
    0112:    77             RR       A
    0113:    B8 1B          MOV      R0, #01BH
    0115:    A0             MOV      @R0, A
    0116:    23 FF          MOV      A, #0FFH
    0118:    54 8B          CALL     0028BH
    011A:    53 FC          ANL      A, #0FCH
    011C:    B8 2E          MOV      R0, #02EH
    011E:    A0             MOV      @R0, A
    011F:    23 FC          MOV      A, #0FCH
    0121:    54 8B          CALL     0028BH
    0123:    AF             MOV      R7, A
    0124:    27             CLR      A
    0125:    B8 15          MOV      R0, #015H
    0127:    A0             MOV      @R0, A
    0128:    18             INC      R0
    0129:    A0             MOV      @R0, A
    012A:    B8 2D          MOV      R0, #02DH
    012C:    B0 40          MOV      @R0, #040H
    012E:    B8 1B          MOV      R0, #01BH
    0130:    F0             MOV      A, @R0
    0131:    53 40          ANL      A, #040H
    0133:    C6 4C          JZ       0004CH
    0135:    B8 3D          MOV      R0, #03DH
    0137:    F0             MOV      A, @R0
    0138:    96 3D          JNZ      0003DH
    013A:    FF             MOV      A, R7
    013B:    24 45          JMP      00145H
    013D:    FF             MOV      A, R7
    013E:    53 FE          ANL      A, #0FEH
    0140:    77             RR       A
    0141:    AA             MOV      R2, A
    0142:    94 8E          CALL     0048EH
    0144:    E7             RL       A
    0145:    B8 2D          MOV      R0, #02DH
    0147:    A0             MOV      @R0, A
    0148:    23 FF          MOV      A, #0FFH
    014A:    54 8B          CALL     0028BH
    014C:    B8 1A          MOV      R0, #01AH
    014E:    F0             MOV      A, @R0
    014F:    07             DEC      A
    0150:    C6 54          JZ       00054H
    0152:    54 BA          CALL     002BAH
    0154:    B8 12          MOV      R0, #012H
    0156:    F0             MOV      A, @R0
    0157:    53 C0          ANL      A, #0C0H
    0159:    37             CPL      A
    015A:    03 C0          ADD      A, #0C0H
    015C:    37             CPL      A
    015D:    96 61          JNZ      00061H
    015F:    64 76          JMP      00376H
    0161:    B9 2B          MOV      R1, #02BH
    0163:    B8 19          MOV      R0, #019H
    0165:    F0             MOV      A, @R0
    0166:    AF             MOV      R7, A
    0167:    B8 1B          MOV      R0, #01BH
    0169:    F0             MOV      A, @R0
    016A:    D2 6F          JB6      0006FH
    016C:    27             CLR      A
    016D:    24 79          JMP      00179H
    016F:    B8 2F          MOV      R0, #02FH
    0171:    F0             MOV      A, @R0
    0172:    F2 76          JB7      00076H
    0174:    24 87          JMP      00187H
    0176:    27             CLR      A
    0177:    24 80          JMP      00180H
    0179:    BA 04          MOV      R2, #004H
    017B:    A1             MOV      @R1, A
    017C:    C9             DEC      R1
    017D:    1F             INC      R7
    017E:    EA 7B          DJNZ     R2, 0007BH
    0180:    BA 02          MOV      R2, #002H
    0182:    A1             MOV      @R1, A
    0183:    C9             DEC      R1
    0184:    1F             INC      R7
    0185:    EA 82          DJNZ     R2, 00082H
    0187:    B8 1D          MOV      R0, #01DH
    0189:    F0             MOV      A, @R0
    018A:    AA             MOV      R2, A
    018B:    B8 12          MOV      R0, #012H
    018D:    F9             MOV      A, R1
    018E:    A0             MOV      @R0, A
    018F:    F0             MOV      A, @R0
    0190:    A9             MOV      R1, A
    0191:    07             DEC      A
    0192:    A0             MOV      @R0, A
    0193:    FF             MOV      A, R7
    0194:    1F             INC      R7
    0195:    E3             MOVP3    A, @A
    0196:    2A             XCH      A, R2
    0197:    5A             ANL      A, R2
    0198:    77             RR       A
    0199:    A1             MOV      @R1, A
    019A:    FA             MOV      A, R2
    019B:    54 8B          CALL     0028BH
    019D:    AA             MOV      R2, A
    019E:    B8 12          MOV      R0, #012H
    01A0:    F0             MOV      A, @R0
    01A1:    37             CPL      A
    01A2:    03 1F          ADD      A, #01FH
    01A4:    37             CPL      A
    01A5:    C6 C0          JZ       000C0H
    01A7:    F0             MOV      A, @R0
    01A8:    A9             MOV      R1, A
    01A9:    07             DEC      A
    01AA:    A0             MOV      @R0, A
    01AB:    FF             MOV      A, R7
    01AC:    1F             INC      R7
    01AD:    E3             MOVP3    A, @A
    01AE:    2A             XCH      A, R2
    01AF:    5A             ANL      A, R2
    01B0:    A1             MOV      @R1, A
    01B1:    FA             MOV      A, R2
    01B2:    54 8B          CALL     0028BH
    01B4:    AA             MOV      R2, A
    01B5:    B8 12          MOV      R0, #012H
    01B7:    F0             MOV      A, @R0
    01B8:    37             CPL      A
    01B9:    03 1F          ADD      A, #01FH
    01BB:    37             CPL      A
    01BC:    C6 C0          JZ       000C0H
    01BE:    24 8F          JMP      0018FH
    01C0:    B8 1B          MOV      R0, #01BH
    01C2:    F0             MOV      A, @R0
    01C3:    F2 C7          JB7      000C7H
    01C5:    44 2E          JMP      0022EH
    01C7:    B8 23          MOV      R0, #023H
    01C9:    F0             MOV      A, @R0
    01CA:    97             CLR      C
    01CB:    F7             RLC      A
    01CC:    A0             MOV      @R0, A
    01CD:    44 2E          JMP      0022EH
    01CF:    44 13          JMP      00213H
    01D1:    B8 15          MOV      R0, #015H
    01D3:    B9 2C          MOV      R1, #02CH
    01D5:    F0             MOV      A, @R0
    01D6:    61             ADD      A, @R1
    01D7:    A1             MOV      @R1, A
    01D8:    18             INC      R0
    01D9:    19             INC      R1
    01DA:    F0             MOV      A, @R0
    01DB:    71             ADDC     A, @R1
    01DC:    A1             MOV      @R1, A
    01DD:    E6 E4          JNC      000E4H
    01DF:    F0             MOV      A, @R0
    01E0:    F2 E4          JB7      000E4H
    01E2:    B1 FF          MOV      @R1, #0FFH
    01E4:    B9 17          MOV      R1, #017H
    01E6:    F1             MOV      A, @R1
    01E7:    96 EB          JNZ      000EBH
    01E9:    44 2E          JMP      0022EH
    01EB:    AB             MOV      R3, A
    01EC:    B8 2E          MOV      R0, #02EH
    01EE:    F0             MOV      A, @R0
    01EF:    53 E0          ANL      A, #0E0H
    01F1:    AA             MOV      R2, A
    01F2:    F0             MOV      A, @R0
    01F3:    53 1F          ANL      A, #01FH
    01F5:    97             CLR      C
    01F6:    6B             ADD      A, R3
    01F7:    F6 CF          JC       000CFH
    01F9:    F2 CF          JB7      000CFH
    01FB:    AC             MOV      R4, A
    01FC:    37             CPL      A
    01FD:    03 20          ADD      A, #020H
    01FF:    37             CPL      A
    0200:    F2 06          JB7      00006H
    0202:    FC             MOV      A, R4
    0203:    03 10          ADD      A, #010H
    0205:    AC             MOV      R4, A
    0206:    FC             MOV      A, R4
    0207:    6A             ADD      A, R2
    0208:    AC             MOV      R4, A
    0209:    F6 0D          JC       0000DH
    020B:    44 2C          JMP      0022CH
    020D:    B1 00          MOV      @R1, #000H
    020F:    BC FF          MOV      R4, #0FFH
    0211:    44 2C          JMP      0022CH
    0213:    53 1F          ANL      A, #01FH
    0215:    AC             MOV      R4, A
    0216:    37             CPL      A
    0217:    03 10          ADD      A, #010H
    0219:    37             CPL      A
    021A:    E6 20          JNC      00020H
    021C:    FC             MOV      A, R4
    021D:    03 F0          ADD      A, #0F0H
    021F:    AC             MOV      R4, A
    0220:    FC             MOV      A, R4
    0221:    6A             ADD      A, R2
    0222:    AC             MOV      R4, A
    0223:    37             CPL      A
    0224:    60             ADD      A, @R0
    0225:    37             CPL      A
    0226:    F6 2C          JC       0002CH
    0228:    B1 00          MOV      @R1, #000H
    022A:    BC 00          MOV      R4, #000H
    022C:    FC             MOV      A, R4
    022D:    A0             MOV      @R0, A
    022E:    56 39          JT1      00039H
    0230:    26 2E          JNT0     0002EH
    0232:    09             IN       A, P1
    0233:    94 3B          CALL     0043BH
    0235:    53 3F          ANL      A, #03FH
    0237:    04 78          JMP      00078H
    0239:    14 2E          CALL     0002EH
    023B:    B8 1A          MOV      R0, #01AH
    023D:    F0             MOV      A, @R0
    023E:    07             DEC      A
    023F:    A0             MOV      @R0, A
    0240:    C6 44          JZ       00044H
    0242:    24 D1          JMP      001D1H
    0244:    B8 2F          MOV      R0, #02FH
    0246:    F0             MOV      A, @R0
    0247:    67             RRC      A
    0248:    E6 4C          JNC      0004CH
    024A:    44 6E          JMP      0026EH
    024C:    B8 1D          MOV      R0, #01DH
    024E:    F0             MOV      A, @R0
    024F:    F7             RLC      A
    0250:    E6 6E          JNC      0006EH
    0252:    F7             RLC      A
    0253:    F6 6E          JC       0006EH
    0255:    53 04          ANL      A, #004H
    0257:    C6 6E          JZ       0006EH
    0259:    B8 1B          MOV      R0, #01BH
    025B:    F0             MOV      A, @R0
    025C:    53 40          ANL      A, #040H
    025E:    96 6E          JNZ      0006EH
    0260:    B0 40          MOV      @R0, #040H
    0262:    C8             DEC      R0
    0263:    B0 01          MOV      @R0, #001H
    0265:    B8 2E          MOV      R0, #02EH
    0267:    B0 00          MOV      @R0, #000H
    0269:    C8             DEC      R0
    026A:    B0 08          MOV      @R0, #008H
    026C:    44 2E          JMP      0022EH
    026E:    B8 1D          MOV      R0, #01DH
    0270:    F0             MOV      A, @R0
    0271:    04 E6          JMP      000E6H
    0273:    F8             MOV      A, R0
    0274:    AE             MOV      R6, A
    0275:    19             INC      R1
    0276:    F1             MOV      A, @R1
    0277:    03 00          ADD      A, #000H
    0279:    3A             OUTL     P2, A
    027A:    C9             DEC      R1
    027B:    F1             MOV      A, @R1
    027C:    A8             MOV      R0, A
    027D:    80             MOVX     A, @R0
    027E:    A8             MOV      R0, A
    027F:    F1             MOV      A, @R1
    0280:    03 01          ADD      A, #001H
    0282:    A1             MOV      @R1, A
    0283:    FE             MOV      A, R6
    0284:    28             XCH      A, R0
    0285:    E6 8A          JNC      0008AH
    0287:    19             INC      R1
    0288:    11             INC      @R1
    0289:    C9             DEC      R1
    028A:    83             RET      
    028B:    B9 13          MOV      R1, #013H
    028D:    B8 1E          MOV      R0, #01EH
    028F:    AB             MOV      R3, A
    0290:    F0             MOV      A, @R0
    0291:    AA             MOV      R2, A
    0292:    B8 1C          MOV      R0, #01CH
    0294:    F0             MOV      A, @R0
    0295:    AC             MOV      R4, A
    0296:    18             INC      R0
    0297:    F0             MOV      A, @R0
    0298:    AD             MOV      R5, A
    0299:    97             CLR      C
    029A:    FB             MOV      A, R3
    029B:    F7             RLC      A
    029C:    AB             MOV      R3, A
    029D:    E6 AE          JNC      000AEH
    029F:    FC             MOV      A, R4
    02A0:    6C             ADD      A, R4
    02A1:    AC             MOV      R4, A
    02A2:    FD             MOV      A, R5
    02A3:    7D             ADDC     A, R5
    02A4:    AD             MOV      R5, A
    02A5:    EA 9A          DJNZ     R2, 0009AH
    02A7:    54 73          CALL     00273H
    02A9:    AC             MOV      R4, A
    02AA:    BA 08          MOV      R2, #008H
    02AC:    44 9A          JMP      0029AH
    02AE:    B8 1E          MOV      R0, #01EH
    02B0:    FA             MOV      A, R2
    02B1:    A0             MOV      @R0, A
    02B2:    B8 1C          MOV      R0, #01CH
    02B4:    FC             MOV      A, R4
    02B5:    A0             MOV      @R0, A
    02B6:    18             INC      R0
    02B7:    FD             MOV      A, R5
    02B8:    A0             MOV      @R0, A
    02B9:    83             RET      
    02BA:    B8 1D          MOV      R0, #01DH
    02BC:    F0             MOV      A, @R0
    02BD:    53 FC          ANL      A, #0FCH
    02BF:    F2 C3          JB7      000C3H
    02C1:    44 C5          JMP      002C5H
    02C3:    37             CPL      A
    02C4:    17             INC      A
    02C5:    AA             MOV      R2, A
    02C6:    B8 1B          MOV      R0, #01BH
    02C8:    F0             MOV      A, @R0
    02C9:    AE             MOV      R6, A
    02CA:    B8 3C          MOV      R0, #03CH
    02CC:    37             CPL      A
    02CD:    D2 D2          JB6      000D2H
    02CF:    94 8E          CALL     0048EH
    02D1:    18             INC      R0
    02D2:    94 8E          CALL     0048EH
    02D4:    53 FC          ANL      A, #0FCH
    02D6:    AA             MOV      R2, A
    02D7:    B8 1D          MOV      R0, #01DH
    02D9:    F0             MOV      A, @R0
    02DA:    F7             RLC      A
    02DB:    FA             MOV      A, R2
    02DC:    E6 E3          JNC      000E3H
    02DE:    C6 E3          JZ       000E3H
    02E0:    37             CPL      A
    02E1:    03 04          ADD      A, #004H
    02E3:    77             RR       A
    02E4:    77             RR       A
    02E5:    B9 17          MOV      R1, #017H
    02E7:    A1             MOV      @R1, A
    02E8:    B9 1A          MOV      R1, #01AH
    02EA:    F1             MOV      A, @R1
    02EB:    07             DEC      A
    02EC:    96 F0          JNZ      000F0H
    02EE:    64 09          JMP      00309H
    02F0:    17             INC      A
    02F1:    E7             RL       A
    02F2:    E7             RL       A
    02F3:    AA             MOV      R2, A
    02F4:    B8 3E          MOV      R0, #03EH
    02F6:    FE             MOV      A, R6
    02F7:    37             CPL      A
    02F8:    D2 FD          JB6      000FDH
    02FA:    94 8E          CALL     0048EH
    02FC:    18             INC      R0
    02FD:    94 8E          CALL     0048EH
    02FF:    77             RR       A
    0300:    77             RR       A
    0301:    53 1F          ANL      A, #01FH
    0303:    96 06          JNZ      00006H
    0305:    17             INC      A
    0306:    B9 1A          MOV      R1, #01AH
    0308:    A1             MOV      @R1, A
    0309:    FE             MOV      A, R6
    030A:    53 40          ANL      A, #040H
    030C:    C6 42          JZ       00042H
    030E:    23 FC          MOV      A, #0FCH
    0310:    54 8B          CALL     0028BH
    0312:    53 FC          ANL      A, #0FCH
    0314:    F2 18          JB7      00018H
    0316:    64 1A          JMP      0031AH
    0318:    37             CPL      A
    0319:    17             INC      A
    031A:    AA             MOV      R2, A
    031B:    B8 3C          MOV      R0, #03CH
    031D:    94 8E          CALL     0048EH
    031F:    18             INC      R0
    0320:    94 8E          CALL     0048EH
    0322:    94 8E          CALL     0048EH
    0324:    53 FC          ANL      A, #0FCH
    0326:    AA             MOV      R2, A
    0327:    B8 1D          MOV      R0, #01DH
    0329:    F8             MOV      A, R0
    032A:    F7             RLC      A
    032B:    FA             MOV      A, R2
    032C:    E6 30          JNC      00030H
    032E:    37             CPL      A
    032F:    17             INC      A
    0330:    47             SWAP     A
    0331:    AA             MOV      R2, A
    0332:    53 C0          ANL      A, #0C0H
    0334:    B8 15          MOV      R0, #015H
    0336:    A0             MOV      @R0, A
    0337:    FA             MOV      A, R2
    0338:    18             INC      R0
    0339:    53 0F          ANL      A, #00FH
    033B:    72 3F          JB3      0003FH
    033D:    64 41          JMP      00341H
    033F:    03 F0          ADD      A, #0F0H
    0341:    A0             MOV      @R0, A
    0342:    23 FC          MOV      A, #0FCH
    0344:    44 8B          JMP      0028BH
    0346:    FC             MOV      A, R4
    0347:    FC             MOV      A, R4
    0348:    FC             MOV      A, R4
    0349:    FC             MOV      A, R4
    034A:    FC             MOV      A, R4
    034B:    FC             MOV      A, R4
    034C:    FC             MOV      A, R4
    034D:    FE             MOV      A, R6
    034E:    FE             MOV      A, R6
    034F:    FF             MOV      A, R7
    0350:    FE             MOV      A, R6
    0351:    FF             MOV      A, R7
    0352:    E0             ???      
    0353:    F8             MOV      A, R0
    0354:    E0             ???      
    0355:    F8             MOV      A, R0
    0356:    E0             ???      
    0357:    F8             MOV      A, R0
    0358:    F0             MOV      A, @R0
    0359:    FC             MOV      A, R4
    035A:    FC             MOV      A, R4
    035B:    FC             MOV      A, R4
    035C:    FE             MOV      A, R6
    035D:    FF             MOV      A, R7
    035E:    F3             ???      
    035F:    F2 F3          JB7      000F3H
    0361:    F2 F3          JB7      000F3H
    0363:    F2 F3          JB7      000F3H
    0365:    FA             MOV      A, R2
    0366:    FB             MOV      A, R3
    0367:    FB             MOV      A, R3
    0368:    FB             MOV      A, R3
    0369:    FB             MOV      A, R3
    036A:    E1             ???      
    036B:    E2             ???      
    036C:    E1             ???      
    036D:    E2             ???      
    036E:    E1             ???      
    036F:    E2             ???      
    0370:    E2             ???      
    0371:    F2 F3          JB7      000F3H
    0373:    F2 FB          JB7      000FBH
    0375:    FB             MOV      A, R3
    0376:    B8 18          MOV      R0, #018H
    0378:    F0             MOV      A, @R0
    0379:    AF             MOV      R7, A
    037A:    B8 1B          MOV      R0, #01BH
    037C:    F0             MOV      A, @R0
    037D:    53 40          ANL      A, #040H
    037F:    C6 90          JZ       00090H
    0381:    B9 2B          MOV      R1, #02BH
    0383:    B8 2F          MOV      R0, #02FH
    0385:    F0             MOV      A, @R0
    0386:    F2 8A          JB7      0008AH
    0388:    64 96          JMP      00396H
    038A:    1F             INC      R7
    038B:    1F             INC      R7
    038C:    C9             DEC      R1
    038D:    C9             DEC      R1
    038E:    64 96          JMP      00396H
    0390:    FF             MOV      A, R7
    0391:    03 06          ADD      A, #006H
    0393:    AF             MOV      R7, A
    0394:    B9 25          MOV      R1, #025H
    0396:    B8 1D          MOV      R0, #01DH
    0398:    F0             MOV      A, @R0
    0399:    AC             MOV      R4, A
    039A:    FF             MOV      A, R7
    039B:    E3             MOVP3    A, @A
    039C:    5C             ANL      A, R4
    039D:    53 FC          ANL      A, #0FCH
    039F:    C6 E1          JZ       000E1H
    03A1:    AC             MOV      R4, A
    03A2:    FF             MOV      A, R7
    03A3:    E3             MOVP3    A, @A
    03A4:    53 03          ANL      A, #003H
    03A6:    AB             MOV      R3, A
    03A7:    F9             MOV      A, R1
    03A8:    37             CPL      A
    03A9:    03 23          ADD      A, #023H
    03AB:    37             CPL      A
    03AC:    96 B5          JNZ      000B5H
    03AE:    B8 1B          MOV      R0, #01BH
    03B0:    F0             MOV      A, @R0
    03B1:    F7             RLC      A
    03B2:    E6 B5          JNC      000B5H
    03B4:    CB             DEC      R3
    03B5:    FC             MOV      A, R4
    03B6:    97             CLR      C
    03B7:    F7             RLC      A
    03B8:    E6 C5          JNC      000C5H
    03BA:    67             RRC      A
    03BB:    CB             DEC      R3
    03BC:    AA             MOV      R2, A
    03BD:    FB             MOV      A, R3
    03BE:    F2 CE          JB7      000CEH
    03C0:    FA             MOV      A, R2
    03C1:    97             CLR      C
    03C2:    A7             CPL      C
    03C3:    64 BA          JMP      003BAH
    03C5:    67             RRC      A
    03C6:    CB             DEC      R3
    03C7:    AA             MOV      R2, A
    03C8:    FB             MOV      A, R3
    03C9:    F2 CE          JB7      000CEH
    03CB:    FA             MOV      A, R2
    03CC:    64 C5          JMP      003C5H
    03CE:    FA             MOV      A, R2
    03CF:    AC             MOV      R4, A
    03D0:    F1             MOV      A, @R1
    03D1:    97             CLR      C
    03D2:    F7             RLC      A
    03D3:    E6 D7          JNC      000D7H
    03D5:    37             CPL      A
    03D6:    17             INC      A
    03D7:    67             RRC      A
    03D8:    6C             ADD      A, R4
    03D9:    97             CLR      C
    03DA:    F7             RLC      A
    03DB:    E6 DF          JNC      000DFH
    03DD:    37             CPL      A
    03DE:    17             INC      A
    03DF:    67             RRC      A
    03E0:    A1             MOV      @R1, A
    03E1:    B8 12          MOV      R0, #012H
    03E3:    F9             MOV      A, R1
    03E4:    A0             MOV      @R0, A
    03E5:    FF             MOV      A, R7
    03E6:    E3             MOVP3    A, @A
    03E7:    54 8B          CALL     0028BH
    03E9:    B8 12          MOV      R0, #012H
    03EB:    F0             MOV      A, @R0
    03EC:    07             DEC      A
    03ED:    A9             MOV      R1, A
    03EE:    1F             INC      R7
    03EF:    37             CPL      A
    03F0:    03 1F          ADD      A, #01FH
    03F2:    37             CPL      A
    03F3:    96 96          JNZ      00096H
    03F5:    44 2E          JMP      0022EH
    03F7:    00             NOP      
    03F8:    00             NOP      
    03F9:    00             NOP      
    03FA:    00             NOP      
    03FB:    B8 2E          MOV      R0, #02EH
    03FD:    27             CLR      A
    03FE:    A0             MOV      @R0, A
    03FF:    B8 15          MOV      R0, #015H
    0401:    BA 03          MOV      R2, #003H
    0403:    A0             MOV      @R0, A
    0404:    18             INC      R0
    0405:    EA 03          DJNZ     R2, 00003H
    0407:    B8 20          MOV      R0, #020H
    0409:    BA 0C          MOV      R2, #00CH
    040B:    A0             MOV      @R0, A
    040C:    18             INC      R0
    040D:    EA 0B          DJNZ     R2, 0000BH
    040F:    B8 2D          MOV      R0, #02DH
    0411:    B0 40          MOV      @R0, #040H
    0413:    B8 1A          MOV      R0, #01AH
    0415:    F0             MOV      A, @R0
    0416:    53 FF          ANL      A, #0FFH
    0418:    96 23          JNZ      00023H
    041A:    17             INC      A
    041B:    A0             MOV      @R0, A
    041C:    B8 2F          MOV      R0, #02FH
    041E:    F0             MOV      A, @R0
    041F:    17             INC      A
    0420:    A0             MOV      @R0, A
    0421:    44 2E          JMP      0022EH
    0423:    07             DEC      A
    0424:    C6 35          JZ       00035H
    0426:    17             INC      A
    0427:    E7             RL       A
    0428:    E7             RL       A
    0429:    AA             MOV      R2, A
    042A:    B8 3E          MOV      R0, #03EH
    042C:    94 8E          CALL     0048EH
    042E:    77             RR       A
    042F:    77             RR       A
    0430:    53 1F          ANL      A, #01FH
    0432:    B8 1A          MOV      R0, #01AH
    0434:    A0             MOV      @R0, A
    0435:    23 FC          MOV      A, #0FCH
    0437:    54 8B          CALL     0028BH
    0439:    44 2E          JMP      0022EH
    043B:    A8             MOV      R0, A
    043C:    27             CLR      A
    043D:    3A             OUTL     P2, A
    043E:    23 7F          MOV      A, #07FH
    0440:    39             OUTL     P1, A
    0441:    23 FF          MOV      A, #0FFH
    0443:    39             OUTL     P1, A
    0444:    F8             MOV      A, R0
    0445:    83             RET      
    0446:    27             CLR      A
    0447:    B8 2E          MOV      R0, #02EH
    0449:    A0             MOV      @R0, A
    044A:    B8 15          MOV      R0, #015H
    044C:    BA 03          MOV      R2, #003H
    044E:    A0             MOV      @R0, A
    044F:    18             INC      R0
    0450:    EA 4E          DJNZ     R2, 0004EH
    0452:    17             INC      A
    0453:    B8 1A          MOV      R0, #01AH
    0455:    A0             MOV      @R0, A
    0456:    37             CPL      A
    0457:    B8 2D          MOV      R0, #02DH
    0459:    A0             MOV      @R0, A
    045A:    B8 1E          MOV      R0, #01EH
    045C:    B0 08          MOV      @R0, #008H
    045E:    B8 30          MOV      R0, #030H
    0460:    B9 30          MOV      R1, #030H
    0462:    18             INC      R0
    0463:    F0             MOV      A, @R0
    0464:    A1             MOV      @R1, A
    0465:    C6 6A          JZ       0006AH
    0467:    19             INC      R1
    0468:    84 62          JMP      00462H
    046A:    B8 1F          MOV      R0, #01FH
    046C:    F9             MOV      A, R1
    046D:    A0             MOV      @R0, A
    046E:    04 96          JMP      00096H
    0470:    AA             MOV      R2, A
    0471:    FE             MOV      A, R6
    0472:    B8 3C          MOV      R0, #03CH
    0474:    B9 3E          MOV      R1, #03EH
    0476:    53 F0          ANL      A, #0F0H
    0478:    A1             MOV      @R1, A
    0479:    C6 7E          JZ       0007EH
    047B:    F7             RLC      A
    047C:    A7             CPL      C
    047D:    67             RRC      A
    047E:    A0             MOV      @R0, A
    047F:    18             INC      R0
    0480:    19             INC      R1
    0481:    FA             MOV      A, R2
    0482:    53 0F          ANL      A, #00FH
    0484:    47             SWAP     A
    0485:    A0             MOV      @R0, A
    0486:    C6 8B          JZ       0008BH
    0488:    F7             RLC      A
    0489:    A7             CPL      C
    048A:    67             RRC      A
    048B:    A1             MOV      @R1, A
    048C:    04 0B          JMP      0000BH
    048E:    F0             MOV      A, @R0
    048F:    C6 BE          JZ       000BEH
    0491:    F7             RLC      A
    0492:    AB             MOV      R3, A
    0493:    FA             MOV      A, R2
    0494:    C6 BF          JZ       000BFH
    0496:    E6 9D          JNC      0009DH
    0498:    37             CPL      A
    0499:    17             INC      A
    049A:    67             RRC      A
    049B:    97             CLR      C
    049C:    A7             CPL      C
    049D:    67             RRC      A
    049E:    AC             MOV      R4, A
    049F:    BD 03          MOV      R5, #003H
    04A1:    FB             MOV      A, R3
    04A2:    F7             RLC      A
    04A3:    AB             MOV      R3, A
    04A4:    E6 B0          JNC      000B0H
    04A6:    FA             MOV      A, R2
    04A7:    6C             ADD      A, R4
    04A8:    AA             MOV      R2, A
    04A9:    37             CPL      A
    04AA:    F2 B0          JB7      000B0H
    04AC:    BA 7F          MOV      R2, #07FH
    04AE:    84 BE          JMP      004BEH
    04B0:    FC             MOV      A, R4
    04B1:    97             CLR      C
    04B2:    F7             RLC      A
    04B3:    E6 B6          JNC      000B6H
    04B5:    17             INC      A
    04B6:    67             RRC      A
    04B7:    67             RRC      A
    04B8:    AC             MOV      R4, A
    04B9:    17             INC      A
    04BA:    C6 BE          JZ       000BEH
    04BC:    ED A1          DJNZ     R5, 000A1H
    04BE:    FA             MOV      A, R2
    04BF:    83             RET      
    04C0:    37             CPL      A
    04C1:    03 3F          ADD      A, #03FH
    04C3:    37             CPL      A
    04C4:    96 D4          JNZ      000D4H
    04C6:    26 C6          JNT0     000C6H
    04C8:    09             IN       A, P1
    04C9:    47             SWAP     A
    04CA:    94 3B          CALL     0043BH
    04CC:    AE             MOV      R6, A
    04CD:    26 CD          JNT0     000CDH
    04CF:    09             IN       A, P1
    04D0:    94 3B          CALL     0043BH
    04D2:    84 70          JMP      00470H
    04D4:    FB             MOV      A, R3
    04D5:    37             CPL      A
    04D6:    03 3E          ADD      A, #03EH
    04D8:    37             CPL      A
    04D9:    C6 DD          JZ       000DDH
    04DB:    04 7B          JMP      0007BH
    04DD:    04 0B          JMP      0000BH
    04DF:    40             ORL      A, @R0
    04E0:    48             ORL      A, R0
    04E1:    40             ORL      A, @R0
    04E2:    48             ORL      A, R0
    04E3:    40             ORL      A, @R0
    04E4:    4C             ORL      A, R4
    04E5:    44 48          JMP      00248H
    04E7:    40             ORL      A, @R0
    04E8:    48             ORL      A, R0
    04E9:    40             ORL      A, @R0
    04EA:    48             ORL      A, R0
    04EB:    40             ORL      A, @R0
    04EC:    48             ORL      A, R0
    04ED:    40             ORL      A, @R0
    04EE:    48             ORL      A, R0
    04EF:    40             ORL      A, @R0
    04F0:    48             ORL      A, R0
    04F1:    40             ORL      A, @R0
    04F2:    48             ORL      A, R0
    04F3:    40             ORL      A, @R0
    04F4:    48             ORL      A, R0
    04F5:    40             ORL      A, @R0
    04F6:    48             ORL      A, R0
    04F7:    40             ORL      A, @R0
    04F8:    48             ORL      A, R0
    04F9:    40             ORL      A, @R0
    04FA:    48             ORL      A, R0
    04FB:    40             ORL      A, @R0
    04FC:    48             ORL      A, R0
    04FD:    40             ORL      A, @R0
    04FE:    48             ORL      A, R0
    04FF:    40             ORL      A, @R0
    0500:    FE             MOV      A, R6
    0501:    C4 7F          JMP      0067FH
    0503:    75             ENT0     CLK
    0504:    7D             ADDC     A, R5
    0505:    75             ENT0     CLK
    0506:    FF             MOV      A, R7
    0507:    F5             SEL      MB1
    0508:    FD             MOV      A, R5
    0509:    F5             SEL      MB1
    050A:    FD             MOV      A, R5
    050B:    F5             SEL      MB1
    050C:    FF             MOV      A, R7
    050D:    F5             SEL      MB1
    050E:    FD             MOV      A, R5
    050F:    F5             SEL      MB1
    0510:    FD             MOV      A, R5
    0511:    F5             SEL      MB1
    0512:    FD             MOV      A, R5
    0513:    F5             SEL      MB1
    0514:    FD             MOV      A, R5
    0515:    F5             SEL      MB1
    0516:    FD             MOV      A, R5
    0517:    F5             SEL      MB1
    0518:    FD             MOV      A, R5
    0519:    F5             SEL      MB1
    051A:    FD             MOV      A, R5
    051B:    F5             SEL      MB1
    051C:    FD             MOV      A, R5
    051D:    F5             SEL      MB1
    051E:    FD             MOV      A, R5
    051F:    F5             SEL      MB1
    0520:    FD             MOV      A, R5
    0521:    F5             SEL      MB1
    0522:    FD             MOV      A, R5
    0523:    F5             SEL      MB1
    0524:    FD             MOV      A, R5
    0525:    F5             SEL      MB1
    0526:    FD             MOV      A, R5
    0527:    F5             SEL      MB1
    0528:    FD             MOV      A, R5
    0529:    F5             SEL      MB1
    052A:    FD             MOV      A, R5
    052B:    F5             SEL      MB1
    052C:    FD             MOV      A, R5
    052D:    F5             SEL      MB1
    052E:    FD             MOV      A, R5
    052F:    F5             SEL      MB1
    0530:    FD             MOV      A, R5
    0531:    F5             SEL      MB1
    0532:    FD             MOV      A, R5
    0533:    F5             SEL      MB1
    0534:    FD             MOV      A, R5
    0535:    F5             SEL      MB1
    0536:    FD             MOV      A, R5
    0537:    F5             SEL      MB1
    0538:    FD             MOV      A, R5
    0539:    F5             SEL      MB1
    053A:    FD             MOV      A, R5
    053B:    F5             SEL      MB1
    053C:    FD             MOV      A, R5
    053D:    F5             SEL      MB1
    053E:    FD             MOV      A, R5
    053F:    F5             SEL      MB1
    0540:    4C             ORL      A, R4
    0541:    44 4C          JMP      0024CH
    0543:    44 4C          JMP      0024CH
    0545:    44 4C          JMP      0024CH
    0547:    44 4C          JMP      0024CH
    0549:    44 4C          JMP      0024CH
    054B:    44 4C          JMP      0024CH
    054D:    44 4C          JMP      0024CH
    054F:    44 48          JMP      00248H
    0551:    40             ORL      A, @R0
    0552:    48             ORL      A, R0
    0553:    40             ORL      A, @R0
    0554:    4C             ORL      A, R4
    0555:    44 4C          JMP      0024CH
    0557:    44 48          JMP      00248H
    0559:    44 48          JMP      00248H
    055B:    40             ORL      A, @R0
    055C:    48             ORL      A, R0
    055D:    40             ORL      A, @R0
    055E:    48             ORL      A, R0
    055F:    40             ORL      A, @R0
    0560:    48             ORL      A, R0
    0561:    40             ORL      A, @R0
    0562:    48             ORL      A, R0
    0563:    40             ORL      A, @R0
    0564:    4C             ORL      A, R4
    0565:    44 48          JMP      00248H
    0567:    40             ORL      A, @R0
    0568:    48             ORL      A, R0
    0569:    40             ORL      A, @R0
    056A:    48             ORL      A, R0
    056B:    40             ORL      A, @R0
    056C:    48             ORL      A, R0
    056D:    40             ORL      A, @R0
    056E:    48             ORL      A, R0
    056F:    40             ORL      A, @R0
    0570:    48             ORL      A, R0
    0571:    40             ORL      A, @R0
    0572:    48             ORL      A, R0
    0573:    40             ORL      A, @R0
    0574:    48             ORL      A, R0
    0575:    40             ORL      A, @R0
    0576:    48             ORL      A, R0
    0577:    40             ORL      A, @R0
    0578:    48             ORL      A, R0
    0579:    40             ORL      A, @R0
    057A:    48             ORL      A, R0
    057B:    40             ORL      A, @R0
    057C:    48             ORL      A, R0
    057D:    40             ORL      A, @R0
    057E:    48             ORL      A, R0
    057F:    40             ORL      A, @R0
    0580:    FE             MOV      A, R6
    0581:    C4 7F          JMP      0067FH
    0583:    77             RR       A
    0584:    7F             ADDC     A, R7
    0585:    75             ENT0     CLK
    0586:    FF             MOV      A, R7
    0587:    F7             RLC      A
    0588:    FD             MOV      A, R5
    0589:    F5             SEL      MB1
    058A:    FD             MOV      A, R5
    058B:    F5             SEL      MB1
    058C:    FF             MOV      A, R7
    058D:    F5             SEL      MB1
    058E:    FF             MOV      A, R7
    058F:    F5             SEL      MB1
    0590:    FD             MOV      A, R5
    0591:    F5             SEL      MB1
    0592:    FD             MOV      A, R5
    0593:    F5             SEL      MB1
    0594:    FD             MOV      A, R5
    0595:    F5             SEL      MB1
    0596:    FD             MOV      A, R5
    0597:    F5             SEL      MB1
    0598:    FD             MOV      A, R5
    0599:    F5             SEL      MB1
    059A:    FD             MOV      A, R5
    059B:    F5             SEL      MB1
    059C:    FD             MOV      A, R5
    059D:    F5             SEL      MB1
    059E:    FD             MOV      A, R5
    059F:    F5             SEL      MB1
    05A0:    FD             MOV      A, R5
    05A1:    F5             SEL      MB1
    05A2:    FD             MOV      A, R5
    05A3:    F5             SEL      MB1
    05A4:    FD             MOV      A, R5
    05A5:    F5             SEL      MB1
    05A6:    FD             MOV      A, R5
    05A7:    F5             SEL      MB1
    05A8:    FD             MOV      A, R5
    05A9:    F5             SEL      MB1
    05AA:    FD             MOV      A, R5
    05AB:    F5             SEL      MB1
    05AC:    FD             MOV      A, R5
    05AD:    F5             SEL      MB1
    05AE:    FD             MOV      A, R5
    05AF:    F5             SEL      MB1
    05B0:    FD             MOV      A, R5
    05B1:    F5             SEL      MB1
    05B2:    FD             MOV      A, R5
    05B3:    F5             SEL      MB1
    05B4:    FD             MOV      A, R5
    05B5:    F5             SEL      MB1
    05B6:    FD             MOV      A, R5
    05B7:    F5             SEL      MB1
    05B8:    FD             MOV      A, R5
    05B9:    F5             SEL      MB1
    05BA:    FD             MOV      A, R5
    05BB:    F5             SEL      MB1
    05BC:    FD             MOV      A, R5
    05BD:    F5             SEL      MB1
    05BE:    FD             MOV      A, R5
    05BF:    F5             SEL      MB1
    05C0:    4C             ORL      A, R4
    05C1:    44 4C          JMP      0024CH
    05C3:    44 4C          JMP      0024CH
    05C5:    44 4C          JMP      0024CH
    05C7:    44 4C          JMP      0024CH
    05C9:    44 4C          JMP      0024CH
    05CB:    44 4C          JMP      0024CH
    05CD:    44 4C          JMP      0024CH
    05CF:    44 48          JMP      00248H
    05D1:    44 48          JMP      00248H
    05D3:    40             ORL      A, @R0
    05D4:    4C             ORL      A, R4
    05D5:    44 4C          JMP      0024CH
    05D7:    44 48          JMP      00248H
    05D9:    44 48          JMP      00248H
    05DB:    40             ORL      A, @R0
    05DC:    48             ORL      A, R0
    05DD:    40             ORL      A, @R0
    05DE:    48             ORL      A, R0
    05DF:    40             ORL      A, @R0
    05E0:    48             ORL      A, R0
    05E1:    40             ORL      A, @R0
    05E2:    48             ORL      A, R0
    05E3:    40             ORL      A, @R0
    05E4:    48             ORL      A, R0
    05E5:    44 48          JMP      00248H
    05E7:    40             ORL      A, @R0
    05E8:    48             ORL      A, R0
    05E9:    40             ORL      A, @R0
    05EA:    48             ORL      A, R0
    05EB:    40             ORL      A, @R0
    05EC:    48             ORL      A, R0
    05ED:    40             ORL      A, @R0
    05EE:    48             ORL      A, R0
    05EF:    40             ORL      A, @R0
    05F0:    48             ORL      A, R0
    05F1:    40             ORL      A, @R0
    05F2:    48             ORL      A, R0
    05F3:    40             ORL      A, @R0
    05F4:    48             ORL      A, R0
    05F5:    40             ORL      A, @R0
    05F6:    48             ORL      A, R0
    05F7:    40             ORL      A, @R0
    05F8:    48             ORL      A, R0
    05F9:    40             ORL      A, @R0
    05FA:    48             ORL      A, R0
    05FB:    40             ORL      A, @R0
    05FC:    48             ORL      A, R0
    05FD:    40             ORL      A, @R0
    05FE:    48             ORL      A, R0
    05FF:    40             ORL      A, @R0
    0600:    FE             MOV      A, R6
    0601:    C4 7F          JMP      0067FH
    0603:    77             RR       A
    0604:    7F             ADDC     A, R7
    0605:    75             ENT0     CLK
    0606:    FF             MOV      A, R7
    0607:    F7             RLC      A
    0608:    FD             MOV      A, R5
    0609:    F5             SEL      MB1
    060A:    FD             MOV      A, R5
    060B:    F5             SEL      MB1
    060C:    FF             MOV      A, R7
    060D:    F5             SEL      MB1
    060E:    FD             MOV      A, R5
    060F:    F5             SEL      MB1
    0610:    FD             MOV      A, R5
    0611:    F5             SEL      MB1
    0612:    FD             MOV      A, R5
    0613:    F5             SEL      MB1
    0614:    FD             MOV      A, R5
    0615:    F5             SEL      MB1
    0616:    FD             MOV      A, R5
    0617:    F5             SEL      MB1
    0618:    FD             MOV      A, R5
    0619:    F5             SEL      MB1
    061A:    FD             MOV      A, R5
    061B:    F5             SEL      MB1
    061C:    FD             MOV      A, R5
    061D:    F5             SEL      MB1
    061E:    FD             MOV      A, R5
    061F:    F5             SEL      MB1
    0620:    FD             MOV      A, R5
    0621:    F5             SEL      MB1
    0622:    FD             MOV      A, R5
    0623:    F5             SEL      MB1
    0624:    FD             MOV      A, R5
    0625:    F5             SEL      MB1
    0626:    FD             MOV      A, R5
    0627:    F5             SEL      MB1
    0628:    FD             MOV      A, R5
    0629:    F5             SEL      MB1
    062A:    FD             MOV      A, R5
    062B:    F5             SEL      MB1
    062C:    FD             MOV      A, R5
    062D:    F5             SEL      MB1
    062E:    FD             MOV      A, R5
    062F:    F5             SEL      MB1
    0630:    FD             MOV      A, R5
    0631:    F5             SEL      MB1
    0632:    FD             MOV      A, R5
    0633:    F5             SEL      MB1
    0634:    FD             MOV      A, R5
    0635:    F5             SEL      MB1
    0636:    FD             MOV      A, R5
    0637:    F5             SEL      MB1
    0638:    FD             MOV      A, R5
    0639:    F5             SEL      MB1
    063A:    FD             MOV      A, R5
    063B:    F5             SEL      MB1
    063C:    FD             MOV      A, R5
    063D:    F5             SEL      MB1
    063E:    FD             MOV      A, R5
    063F:    F5             SEL      MB1
    0640:    4C             ORL      A, R4
    0641:    44 4C          JMP      0024CH
    0643:    44 4C          JMP      0024CH
    0645:    44 4C          JMP      0024CH
    0647:    44 4C          JMP      0024CH
    0649:    44 4C          JMP      0024CH
    064B:    44 4C          JMP      0024CH
    064D:    44 4C          JMP      0024CH
    064F:    44 48          JMP      00248H
    0651:    44 48          JMP      00248H
    0653:    44 4C          JMP      0024CH
    0655:    44 4C          JMP      0024CH
    0657:    44 48          JMP      00248H
    0659:    44 48          JMP      00248H
    065B:    40             ORL      A, @R0
    065C:    48             ORL      A, R0
    065D:    44 48          JMP      00248H
    065F:    40             ORL      A, @R0
    0660:    48             ORL      A, R0
    0661:    40             ORL      A, @R0
    0662:    48             ORL      A, R0
    0663:    40             ORL      A, @R0
    0664:    4C             ORL      A, R4
    0665:    44 48          JMP      00248H
    0667:    40             ORL      A, @R0
    0668:    48             ORL      A, R0
    0669:    40             ORL      A, @R0
    066A:    48             ORL      A, R0
    066B:    40             ORL      A, @R0
    066C:    48             ORL      A, R0
    066D:    40             ORL      A, @R0
    066E:    48             ORL      A, R0
    066F:    40             ORL      A, @R0
    0670:    48             ORL      A, R0
    0671:    40             ORL      A, @R0
    0672:    48             ORL      A, R0
    0673:    40             ORL      A, @R0
    0674:    48             ORL      A, R0
    0675:    40             ORL      A, @R0
    0676:    48             ORL      A, R0
    0677:    40             ORL      A, @R0
    0678:    48             ORL      A, R0
    0679:    40             ORL      A, @R0
    067A:    48             ORL      A, R0
    067B:    40             ORL      A, @R0
    067C:    48             ORL      A, R0
    067D:    40             ORL      A, @R0
    067E:    48             ORL      A, R0
    067F:    40             ORL      A, @R0
    0680:    FE             MOV      A, R6
    0681:    C4 7F          JMP      0067FH
    0683:    77             RR       A
    0684:    7F             ADDC     A, R7
    0685:    75             ENT0     CLK
    0686:    FF             MOV      A, R7
    0687:    F7             RLC      A
    0688:    FD             MOV      A, R5
    0689:    F5             SEL      MB1
    068A:    FD             MOV      A, R5
    068B:    F5             SEL      MB1
    068C:    FF             MOV      A, R7
    068D:    F5             SEL      MB1
    068E:    FD             MOV      A, R5
    068F:    F5             SEL      MB1
    0690:    FD             MOV      A, R5
    0691:    F5             SEL      MB1
    0692:    FD             MOV      A, R5
    0693:    F5             SEL      MB1
    0694:    FD             MOV      A, R5
    0695:    F5             SEL      MB1
    0696:    FD             MOV      A, R5
    0697:    F5             SEL      MB1
    0698:    FD             MOV      A, R5
    0699:    F5             SEL      MB1
    069A:    FD             MOV      A, R5
    069B:    F5             SEL      MB1
    069C:    FD             MOV      A, R5
    069D:    F5             SEL      MB1
    069E:    FD             MOV      A, R5
    069F:    F5             SEL      MB1
    06A0:    FD             MOV      A, R5
    06A1:    F5             SEL      MB1
    06A2:    FD             MOV      A, R5
    06A3:    F5             SEL      MB1
    06A4:    FD             MOV      A, R5
    06A5:    F5             SEL      MB1
    06A6:    FD             MOV      A, R5
    06A7:    F5             SEL      MB1
    06A8:    FD             MOV      A, R5
    06A9:    F5             SEL      MB1
    06AA:    FD             MOV      A, R5
    06AB:    F5             SEL      MB1
    06AC:    FD             MOV      A, R5
    06AD:    F5             SEL      MB1
    06AE:    FD             MOV      A, R5
    06AF:    F5             SEL      MB1
    06B0:    FD             MOV      A, R5
    06B1:    F5             SEL      MB1
    06B2:    FD             MOV      A, R5
    06B3:    F5             SEL      MB1
    06B4:    FD             MOV      A, R5
    06B5:    F5             SEL      MB1
    06B6:    FD             MOV      A, R5
    06B7:    F5             SEL      MB1
    06B8:    FD             MOV      A, R5
    06B9:    F5             SEL      MB1
    06BA:    FD             MOV      A, R5
    06BB:    F5             SEL      MB1
    06BC:    FD             MOV      A, R5
    06BD:    F5             SEL      MB1
    06BE:    FD             MOV      A, R5
    06BF:    F5             SEL      MB1
    06C0:    4C             ORL      A, R4
    06C1:    44 4C          JMP      0024CH
    06C3:    44 4C          JMP      0024CH
    06C5:    44 4C          JMP      0024CH
    06C7:    44 4C          JMP      0024CH
    06C9:    44 4C          JMP      0024CH
    06CB:    44 4C          JMP      0024CH
    06CD:    44 4C          JMP      0024CH
    06CF:    44 4C          JMP      0024CH
    06D1:    44 4C          JMP      0024CH
    06D3:    44 4C          JMP      0024CH
    06D5:    44 4C          JMP      0024CH
    06D7:    44 4C          JMP      0024CH
    06D9:    44 48          JMP      00248H
    06DB:    44 4C          JMP      0024CH
    06DD:    44 48          JMP      00248H
    06DF:    44 4C          JMP      0024CH
    06E1:    44 48          JMP      00248H
    06E3:    40             ORL      A, @R0
    06E4:    4C             ORL      A, R4
    06E5:    44 48          JMP      00248H
    06E7:    40             ORL      A, @R0
    06E8:    48             ORL      A, R0
    06E9:    40             ORL      A, @R0
    06EA:    48             ORL      A, R0
    06EB:    40             ORL      A, @R0
    06EC:    48             ORL      A, R0
    06ED:    40             ORL      A, @R0
    06EE:    48             ORL      A, R0
    06EF:    40             ORL      A, @R0
    06F0:    48             ORL      A, R0
    06F1:    40             ORL      A, @R0
    06F2:    48             ORL      A, R0
    06F3:    40             ORL      A, @R0
    06F4:    48             ORL      A, R0
    06F5:    40             ORL      A, @R0
    06F6:    48             ORL      A, R0
    06F7:    40             ORL      A, @R0
    06F8:    48             ORL      A, R0
    06F9:    40             ORL      A, @R0
    06FA:    48             ORL      A, R0
    06FB:    40             ORL      A, @R0
    06FC:    48             ORL      A, R0
    06FD:    40             ORL      A, @R0
    06FE:    48             ORL      A, R0
    06FF:    40             ORL      A, @R0
    0700:    FE             MOV      A, R6
    0701:    C4 7F          JMP      0067FH
    0703:    77             RR       A
    0704:    7F             ADDC     A, R7
    0705:    75             ENT0     CLK
    0706:    FF             MOV      A, R7
    0707:    F5             SEL      MB1
    0708:    FD             MOV      A, R5
    0709:    F5             SEL      MB1
    070A:    FD             MOV      A, R5
    070B:    F5             SEL      MB1
    070C:    FF             MOV      A, R7
    070D:    F5             SEL      MB1
    070E:    FD             MOV      A, R5
    070F:    F5             SEL      MB1
    0710:    FD             MOV      A, R5
    0711:    F5             SEL      MB1
    0712:    FD             MOV      A, R5
    0713:    F5             SEL      MB1
    0714:    FD             MOV      A, R5
    0715:    F5             SEL      MB1
    0716:    FD             MOV      A, R5
    0717:    F5             SEL      MB1
    0718:    FD             MOV      A, R5
    0719:    F5             SEL      MB1
    071A:    FD             MOV      A, R5
    071B:    F5             SEL      MB1
    071C:    FD             MOV      A, R5
    071D:    F5             SEL      MB1
    071E:    FD             MOV      A, R5
    071F:    F5             SEL      MB1
    0720:    FD             MOV      A, R5
    0721:    F5             SEL      MB1
    0722:    FD             MOV      A, R5
    0723:    F5             SEL      MB1
    0724:    FD             MOV      A, R5
    0725:    F5             SEL      MB1
    0726:    FD             MOV      A, R5
    0727:    F5             SEL      MB1
    0728:    FD             MOV      A, R5
    0729:    F5             SEL      MB1
    072A:    FD             MOV      A, R5
    072B:    F5             SEL      MB1
    072C:    FD             MOV      A, R5
    072D:    F5             SEL      MB1
    072E:    FD             MOV      A, R5
    072F:    F5             SEL      MB1
    0730:    FD             MOV      A, R5
    0731:    F5             SEL      MB1
    0732:    FD             MOV      A, R5
    0733:    F5             SEL      MB1
    0734:    FD             MOV      A, R5
    0735:    F5             SEL      MB1
    0736:    FD             MOV      A, R5
    0737:    F5             SEL      MB1
    0738:    FD             MOV      A, R5
    0739:    F5             SEL      MB1
    073A:    FD             MOV      A, R5
    073B:    F5             SEL      MB1
    073C:    FD             MOV      A, R5
    073D:    F5             SEL      MB1
    073E:    FD             MOV      A, R5
    073F:    F5             SEL      MB1
    0740:    4C             ORL      A, R4
    0741:    44 4C          JMP      0024CH
    0743:    44 4C          JMP      0024CH
    0745:    44 4C          JMP      0024CH
    0747:    44 4C          JMP      0024CH
    0749:    44 4C          JMP      0024CH
    074B:    44 4C          JMP      0024CH
    074D:    44 4C          JMP      0024CH
    074F:    44 48          JMP      00248H
    0751:    40             ORL      A, @R0
    0752:    48             ORL      A, R0
    0753:    44 4C          JMP      0024CH
    0755:    44 4C          JMP      0024CH
    0757:    44 48          JMP      00248H
    0759:    44 48          JMP      00248H
    075B:    40             ORL      A, @R0
    075C:    48             ORL      A, R0
    075D:    40             ORL      A, @R0
    075E:    48             ORL      A, R0
    075F:    40             ORL      A, @R0
    0760:    48             ORL      A, R0
    0761:    40             ORL      A, @R0
    0762:    48             ORL      A, R0
    0763:    40             ORL      A, @R0
    0764:    48             ORL      A, R0
    0765:    40             ORL      A, @R0
    0766:    48             ORL      A, R0
    0767:    40             ORL      A, @R0
    0768:    48             ORL      A, R0
    0769:    40             ORL      A, @R0
    076A:    48             ORL      A, R0
    076B:    40             ORL      A, @R0
    076C:    48             ORL      A, R0
    076D:    40             ORL      A, @R0
    076E:    48             ORL      A, R0
    076F:    40             ORL      A, @R0
    0770:    48             ORL      A, R0
    0771:    40             ORL      A, @R0
    0772:    48             ORL      A, R0
    0773:    40             ORL      A, @R0
    0774:    48             ORL      A, R0
    0775:    40             ORL      A, @R0
    0776:    48             ORL      A, R0
    0777:    40             ORL      A, @R0
    0778:    48             ORL      A, R0
    0779:    40             ORL      A, @R0
    077A:    48             ORL      A, R0
    077B:    40             ORL      A, @R0
    077C:    48             ORL      A, R0
    077D:    40             ORL      A, @R0
    077E:    48             ORL      A, R0
    077F:    40             ORL      A, @R0
    0780:    FE             MOV      A, R6
    0781:    C4 7F          JMP      0067FH
    0783:    77             RR       A
    0784:    7F             ADDC     A, R7
    0785:    75             ENT0     CLK
    0786:    FF             MOV      A, R7
    0787:    F7             RLC      A
    0788:    FD             MOV      A, R5
    0789:    F5             SEL      MB1
    078A:    FD             MOV      A, R5
    078B:    F5             SEL      MB1
    078C:    FF             MOV      A, R7
    078D:    F5             SEL      MB1
    078E:    FF             MOV      A, R7
    078F:    F5             SEL      MB1
    0790:    FD             MOV      A, R5
    0791:    F5             SEL      MB1
    0792:    FD             MOV      A, R5
    0793:    F5             SEL      MB1
    0794:    FD             MOV      A, R5
    0795:    F5             SEL      MB1
    0796:    FD             MOV      A, R5
    0797:    F5             SEL      MB1
    0798:    FD             MOV      A, R5
    0799:    F5             SEL      MB1
    079A:    FD             MOV      A, R5
    079B:    F5             SEL      MB1
    079C:    FD             MOV      A, R5
    079D:    F5             SEL      MB1
    079E:    FD             MOV      A, R5
    079F:    F5             SEL      MB1
    07A0:    FD             MOV      A, R5
    07A1:    F5             SEL      MB1
    07A2:    FD             MOV      A, R5
    07A3:    F5             SEL      MB1
    07A4:    FD             MOV      A, R5
    07A5:    F5             SEL      MB1
    07A6:    FD             MOV      A, R5
    07A7:    F5             SEL      MB1
    07A8:    FD             MOV      A, R5
    07A9:    F5             SEL      MB1
    07AA:    FD             MOV      A, R5
    07AB:    F5             SEL      MB1
    07AC:    FD             MOV      A, R5
    07AD:    F5             SEL      MB1
    07AE:    FD             MOV      A, R5
    07AF:    F5             SEL      MB1
    07B0:    FD             MOV      A, R5
    07B1:    F5             SEL      MB1
    07B2:    FD             MOV      A, R5
    07B3:    F5             SEL      MB1
    07B4:    FD             MOV      A, R5
    07B5:    F5             SEL      MB1
    07B6:    FD             MOV      A, R5
    07B7:    F5             SEL      MB1
    07B8:    FD             MOV      A, R5
    07B9:    F5             SEL      MB1
    07BA:    FD             MOV      A, R5
    07BB:    F5             SEL      MB1
    07BC:    FD             MOV      A, R5
    07BD:    F5             SEL      MB1
    07BE:    FD             MOV      A, R5
    07BF:    F5             SEL      MB1
    07C0:    4C             ORL      A, R4
    07C1:    44 4C          JMP      0024CH
    07C3:    44 4C          JMP      0024CH
    07C5:    44 4C          JMP      0024CH
    07C7:    44 4C          JMP      0024CH
    07C9:    44 4C          JMP      0024CH
    07CB:    44 4C          JMP      0024CH
    07CD:    44 4C          JMP      0024CH
    07CF:    44 48          JMP      00248H
    07D1:    44 4C          JMP      0024CH
    07D3:    44 4C          JMP      0024CH
    07D5:    44 4C          JMP      0024CH
    07D7:    44 48          JMP      00248H
    07D9:    44 48          JMP      00248H
    07DB:    40             ORL      A, @R0
    07DC:    48             ORL      A, R0
    07DD:    44 48          JMP      00248H
    07DF:    40             ORL      A, @R0
    07E0:    48             ORL      A, R0
    07E1:    40             ORL      A, @R0
    07E2:    48             ORL      A, R0
    07E3:    40             ORL      A, @R0
    07E4:    4C             ORL      A, R4
    07E5:    40             ORL      A, @R0
    07E6:    48             ORL      A, R0
    07E7:    40             ORL      A, @R0
    07E8:    48             ORL      A, R0
    07E9:    40             ORL      A, @R0
    07EA:    48             ORL      A, R0
    07EB:    40             ORL      A, @R0
    07EC:    48             ORL      A, R0
    07ED:    40             ORL      A, @R0
    07EE:    48             ORL      A, R0
    07EF:    40             ORL      A, @R0
    07F0:    48             ORL      A, R0
    07F1:    40             ORL      A, @R0
    07F2:    48             ORL      A, R0
    07F3:    40             ORL      A, @R0
    07F4:    48             ORL      A, R0
    07F5:    40             ORL      A, @R0
    07F6:    48             ORL      A, R0
    07F7:    40             ORL      A, @R0
    07F8:    48             ORL      A, R0
    07F9:    40             ORL      A, @R0
    07FA:    48             ORL      A, R0
    07FB:    40             ORL      A, @R0
    07FC:    48             ORL      A, R0
    07FD:    40             ORL      A, @R0
    07FE:    48             ORL      A, R0

