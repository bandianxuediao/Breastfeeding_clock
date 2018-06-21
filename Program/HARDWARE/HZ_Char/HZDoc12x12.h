/*本文件为12×12点阵中文字库文件,字的横向8点构成一字节,左边点在字节的高位,字符点阵四角按左上角→右上角→左下角→右下角取字*/
/*如你想在以后继续用HZDotReader打开文件,追加汉字点阵数据,请不要修改或增删所有注释*/

#define  hzNum  81

unsigned char code hzIndex[162] =
{
	0xa1, 0xcc, 0xa1, 0xfc, 0xa1, 0xfd, 0xb0, 0xb4, 0xb1, 0xa3, 0xb1, 0xa6, 0xb1, 0xe3, 0xb1, 0xed,
	0xb2, 0xb8, 0xb2, 0xb9, 0xb2, 0xcb, 0xb2, 0xd9, 0xb2, 0xe9, 0xb3, 0xa4, 0xb3, 0xac, 0xb3, 0xc9,
	0xb3, 0xfd, 0xb4, 0xe6, 0xb4, 0xf3, 0xb5, 0xa5, 0xb7, 0xad, 0xb7, 0xb5, 0xb7, 0xd6, 0xb7, 0xf1,
	0xb8, 0xc4, 0xb9, 0xa6, 0xb9, 0xb2, 0xbb, 0xd8, 0xbc, 0xb4, 0xbc, 0xc7, 0xbc, 0xce, 0xbc, 0xe4,
	0xbd, 0xa1, 0xbd, 0xab, 0xbd, 0xe7, 0xbe, 0xdd, 0xbf, 0xb4, 0xbf, 0xb5, 0xbf, 0xd5, 0xbf, 0xec,
	0xc0, 0xd6, 0xc0, 0xee, 0xc1, 0xd0, 0xc2, 0xbc, 0xc3, 0xe6, 0xc3, 0xeb, 0xc4, 0xea, 0xc6, 0xda,
	0xc6, 0xf7, 0xc7, 0xe5, 0xc7, 0xeb, 0xc8, 0xa1, 0xc8, 0xb7, 0xc8, 0xcf, 0xc8, 0xd5, 0xc8, 0xe9,
	0xc9, 0xbe, 0xc9, 0xcf, 0xca, 0xb1, 0xca, 0xc7, 0xca, 0xfd, 0xcb, 0xae, 0xcb, 0xf9, 0xcc, 0xf5,
	0xce, 0xde, 0xcf, 0xc2, 0xd0, 0xa1, 0xd0, 0xd0, 0xd0, 0xde, 0xd1, 0xa1, 0xd2, 0xb3, 0xd2, 0xbb,
	0xd3, 0xd0, 0xd4, 0xb8, 0xd4, 0xc2, 0xd4, 0xf1, 0xd6, 0xb4, 0xd6, 0xd0, 0xd6, 0xf7, 0xd7, 0xf7,
	0xee, 0xc8
};

unsigned char code hzdot[1944] =
{
	/*√   CA1CC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x20, 0x00, 0x40, 0x00, 0x80, 0x41, 0x00, 0xC2, 0x00,
	0x24, 0x00, 0x28, 0x00, 0x10, 0x00, 0x00, 0x00,

	/*↑   CA1FC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 0x0E, 0x00, 0x0E, 0x00,
	0x15, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00,

	/*↓   CA1FD */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x15, 0x00,
	0x0E, 0x00, 0x0E, 0x00, 0x04, 0x00, 0x04, 0x00,

	/*按   CB0B4 */
	0x21, 0x00, 0x21, 0x00, 0xF7, 0xF0, 0x28, 0x20, 0x21, 0x00, 0x3F, 0xF0, 0xE2, 0x40, 0x24, 0x40,
	0x22, 0x80, 0x21, 0x80, 0xA2, 0x60, 0x4C, 0x20,

	/*保   CB1A3 */
	0x10, 0x40, 0x17, 0xE0, 0x24, 0x40, 0x24, 0x40, 0x67, 0xC0, 0xA1, 0x00, 0x3F, 0xF0, 0x23, 0x00,
	0x25, 0x80, 0x29, 0x40, 0x31, 0x30, 0x21, 0x00,

	/*宝   CB1A6 */
	0x04, 0x00, 0x7F, 0xF0, 0x40, 0x10, 0x80, 0xA0, 0x3F, 0xC0, 0x04, 0x00, 0x04, 0x00, 0x3F, 0xC0,
	0x05, 0x00, 0x04, 0x80, 0x04, 0x20, 0xFF, 0xF0,

	/*便   CB1E3 */
	0x10, 0x20, 0x1F, 0xF0, 0x21, 0x00, 0x2F, 0xE0, 0x69, 0x20, 0xAF, 0xE0, 0x29, 0x20, 0x2F, 0xE0,
	0x25, 0x00, 0x23, 0x00, 0x24, 0xF0, 0x38, 0x20,

	/*表   CB1ED */
	0x04, 0x00, 0x04, 0x40, 0x7F, 0xE0, 0x04, 0x00, 0x3F, 0xC0, 0x04, 0x00, 0xFF, 0xF0, 0x1A, 0x20,
	0x29, 0x40, 0x48, 0x80, 0x8E, 0x40, 0x18, 0x30,

	/*哺   CB2B8 */
	0x01, 0x40, 0x11, 0x20, 0xFF, 0xF0, 0x91, 0x00, 0x97, 0xE0, 0x95, 0x20, 0x97, 0xE0, 0xF5, 0x20,
	0x97, 0xE0, 0x05, 0x20, 0x05, 0x20, 0x05, 0x60,

	/*补   CB2B9 */
	0x20, 0x80, 0x10, 0x80, 0xFC, 0x80, 0x08, 0x80, 0x10, 0xC0, 0x34, 0xA0, 0x58, 0x90, 0x94, 0x80,
	0x10, 0x80, 0x10, 0x80, 0x10, 0x80, 0x10, 0x80,

	/*菜   CB2CB */
	0x09, 0x20, 0xFF, 0xF0, 0x09, 0x00, 0x01, 0xE0, 0x7E, 0x40, 0x24, 0x80, 0x12, 0x20, 0xFF, 0xF0,
	0x0B, 0x00, 0x12, 0x80, 0x62, 0x70, 0x82, 0x20,

	/*操   CB2D9 */
	0x27, 0xC0, 0x24, 0x40, 0xF7, 0xC0, 0x20, 0x00, 0x3E, 0xE0, 0x6A, 0xA0, 0xAE, 0xE0, 0x21, 0x00,
	0x3F, 0xF0, 0x25, 0x40, 0xA9, 0x20, 0x51, 0x10,

	/*查   CB2E9 */
	0x04, 0x00, 0xFF, 0xF0, 0x0D, 0x00, 0x14, 0x80, 0x24, 0x40, 0x5F, 0xB0, 0x90, 0x80, 0x1F, 0x80,
	0x10, 0x80, 0x1F, 0x80, 0x00, 0x00, 0xFF, 0xF0,

	/*长   CB3A4 */
	0x10, 0x40, 0x10, 0x80, 0x11, 0x00, 0x16, 0x00, 0x18, 0x20, 0xFF, 0xF0, 0x14, 0x00, 0x12, 0x00,
	0x11, 0x00, 0x10, 0x80, 0x1C, 0x70, 0x10, 0x00,

	/*超   CB3AC */
	0x10, 0x20, 0x13, 0xF0, 0x7D, 0x20, 0x11, 0x20, 0xFA, 0xC0, 0x14, 0x00, 0x53, 0xE0, 0x5A, 0x20,
	0x52, 0x20, 0xB3, 0xE0, 0x98, 0x00, 0x07, 0xF0,

	/*成   CB3C9 */
	0x02, 0x80, 0x02, 0x40, 0x3F, 0xF0, 0x22, 0x00, 0x22, 0x40, 0x3A, 0x40, 0x29, 0x40, 0x29, 0x40,
	0x28, 0x90, 0x59, 0x90, 0x42, 0x50, 0x8C, 0x30,

	/*除   CB3FD */
	0x01, 0x00, 0xF2, 0x80, 0x92, 0x40, 0xA4, 0x30, 0xCF, 0xC0, 0xA1, 0x00, 0x9F, 0xF0, 0xD1, 0x00,
	0xB5, 0x40, 0x89, 0x20, 0x93, 0x10, 0x81, 0x00,

	/*存   CB4E6 */
	0x04, 0x20, 0xFF, 0xF0, 0x08, 0x00, 0x17, 0xE0, 0x20, 0x40, 0x20, 0x80, 0x61, 0x20, 0xBF, 0xF0,
	0x21, 0x00, 0x21, 0x00, 0x25, 0x00, 0x23, 0x00,

	/*大   CB4F3 */
	0x04, 0x00, 0x04, 0x00, 0x04, 0x20, 0xFF, 0xF0, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x0A, 0x00,
	0x09, 0x00, 0x10, 0x80, 0x20, 0x70, 0xC0, 0x20,

	/*单   CB5A5 */
	0x10, 0x80, 0x09, 0x00, 0x3F, 0xC0, 0x24, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x3F, 0xC0, 0x24, 0x00,
	0x04, 0x20, 0xFF, 0xF0, 0x04, 0x00, 0x04, 0x00,

	/*翻   CB7AD */
	0x1C, 0x00, 0xF3, 0xB0, 0x54, 0x90, 0xFE, 0x90, 0x59, 0xB0, 0x90, 0x90, 0x7D, 0xF0, 0x56, 0x90,
	0x7C, 0x90, 0x54, 0x90, 0x7C, 0x90, 0x01, 0x20,

	/*返   CB7B5 */
	0x40, 0xE0, 0x27, 0x00, 0x24, 0x00, 0x07, 0xE0, 0x04, 0x20, 0xE6, 0x40, 0x25, 0x40, 0x28, 0x80,
	0x31, 0x40, 0x26, 0x20, 0x50, 0x00, 0x8F, 0xF0,

	/*分   CB7D6 */
	0x09, 0x00, 0x09, 0x00, 0x11, 0x00, 0x10, 0x80, 0x20, 0x40, 0x7F, 0xB0, 0x88, 0x80, 0x08, 0x80,
	0x08, 0x80, 0x10, 0x80, 0x12, 0x80, 0x61, 0x00,

	/*否   CB7F1 */
	0x00, 0x20, 0xFF, 0xF0, 0x04, 0x00, 0x0D, 0x80, 0x14, 0x60, 0x64, 0x30, 0x84, 0x40, 0x3F, 0xC0,
	0x20, 0x40, 0x20, 0x40, 0x3F, 0xC0, 0x20, 0x40,

	/*改   CB8C4 */
	0x01, 0x00, 0x09, 0x00, 0xFD, 0x20, 0x0B, 0xF0, 0x0A, 0x40, 0x7D, 0x40, 0x49, 0x40, 0x41, 0x40,
	0x48, 0x80, 0x70, 0x80, 0x43, 0x40, 0x1C, 0x30,

	/*功   CB9A6 */
	0x01, 0x00, 0x11, 0x00, 0xF9, 0x20, 0x27, 0xF0, 0x21, 0x20, 0x21, 0x20, 0x21, 0x20, 0x39, 0x20,
	0xC2, 0x20, 0x04, 0x20, 0x08, 0xA0, 0x30, 0x40,

	/*共   CB9B2 */
	0x08, 0x80, 0x08, 0x80, 0x08, 0x80, 0x7F, 0xE0, 0x08, 0x80, 0x08, 0x80, 0x08, 0x80, 0xFF, 0xF0,
	0x00, 0x00, 0x18, 0x80, 0x20, 0x60, 0xC0, 0x20,

	/*回   CBBD8 */
	0x00, 0x20, 0x7F, 0xF0, 0x40, 0x20, 0x4F, 0x20, 0x49, 0x20, 0x49, 0x20, 0x49, 0x20, 0x4F, 0x20,
	0x40, 0x20, 0x40, 0x20, 0x7F, 0xE0, 0x40, 0x20,

	/*即   CBCB4 */
	0x00, 0x20, 0x7D, 0xF0, 0x45, 0x20, 0x7D, 0x20, 0x45, 0x20, 0x7D, 0x20, 0x41, 0x20, 0x49, 0x20,
	0x49, 0x60, 0x75, 0x00, 0x41, 0x00, 0x01, 0x00,

	/*记   CBCC7 */
	0x40, 0x20, 0x27, 0xF0, 0x20, 0x20, 0x00, 0x20, 0xE0, 0x20, 0x27, 0xE0, 0x24, 0x00, 0x24, 0x00,
	0x2C, 0x10, 0x34, 0x10, 0x24, 0x10, 0x03, 0xF0,

	/*嘉   CBCCE */
	0x04, 0x20, 0xFF, 0xF0, 0x04, 0x00, 0x7F, 0xC0, 0x20, 0x80, 0x3F, 0x80, 0x11, 0x20, 0xFF, 0xF0,
	0x10, 0x00, 0x7D, 0xE0, 0x25, 0x20, 0xCD, 0xE0,

	/*间   CBCE4 */
	0x20, 0x20, 0x17, 0xF0, 0x40, 0x20, 0x4F, 0x20, 0x49, 0x20, 0x4F, 0x20, 0x49, 0x20, 0x49, 0x20,
	0x4F, 0x20, 0x48, 0x20, 0x40, 0xA0, 0x40, 0x60,

	/*健   CBDA1 */
	0x20, 0x80, 0x3B, 0xE0, 0x28, 0xA0, 0x4F, 0xF0, 0x68, 0xA0, 0xBF, 0xE0, 0x24, 0x80, 0x27, 0xF0,
	0x28, 0x80, 0x2B, 0xE0, 0x34, 0x80, 0x23, 0xF0,

	/*将   CBDAB */
	0x21, 0x00, 0x23, 0xE0, 0xA4, 0x20, 0xAA, 0x40, 0x61, 0x80, 0x26, 0x40, 0x20, 0x40, 0x6F, 0xF0,
	0xA0, 0x40, 0x26, 0x40, 0x21, 0x40, 0x20, 0xC0,

	/*界   CBDE7 */
	0x3F, 0xC0, 0x24, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x3F, 0xC0, 0x04, 0x00, 0x0B, 0x00, 0x38, 0xF0,
	0xC9, 0x20, 0x09, 0x00, 0x11, 0x00, 0x61, 0x00,

	/*据   CBEDD */
	0x20, 0x20, 0x27, 0xF0, 0x24, 0x20, 0xFF, 0xE0, 0x24, 0x80, 0x37, 0xF0, 0xE4, 0x80, 0x24, 0xA0,
	0x2B, 0xF0, 0x2A, 0x20, 0xAB, 0xE0, 0x52, 0x20,

	/*看   CBFB4 */
	0x03, 0xC0, 0x7C, 0x00, 0x04, 0x40, 0x3F, 0xE0, 0x08, 0x00, 0xFF, 0xF0, 0x30, 0x40, 0x5F, 0xC0,
	0x90, 0x40, 0x1F, 0xC0, 0x10, 0x40, 0x1F, 0xC0,

	/*康   CBFB5 */
	0x02, 0x20, 0x7F, 0xF0, 0x42, 0x00, 0x5F, 0xC0, 0x42, 0x40, 0x7F, 0xF0, 0x42, 0x40, 0x5F, 0xC0,
	0x4B, 0x40, 0x92, 0x80, 0xA2, 0x40, 0x06, 0x30,

	/*空   CBFD5 */
	0x04, 0x00, 0x02, 0x00, 0x7F, 0xF0, 0x80, 0x10, 0x11, 0x80, 0x20, 0x60, 0xC0, 0x20, 0x3F, 0xC0,
	0x04, 0x00, 0x04, 0x00, 0x04, 0x20, 0xFF, 0xF0,

	/*快   CBFEC */
	0x21, 0x00, 0x21, 0x00, 0x27, 0xE0, 0xB1, 0x20, 0xA9, 0x20, 0xA1, 0x20, 0x2F, 0xF0, 0x21, 0x00,
	0x22, 0x80, 0x22, 0x40, 0x24, 0x20, 0x28, 0x10,

	/*乐   CC0D6 */
	0x03, 0xC0, 0x3E, 0x00, 0x20, 0x00, 0x22, 0x00, 0x42, 0x20, 0x7F, 0xF0, 0x02, 0x00, 0x12, 0x80,
	0x22, 0x40, 0x42, 0x20, 0x8A, 0x20, 0x04, 0x00,

	/*李   CC0EE */
	0x02, 0x20, 0x7F, 0xF0, 0x0B, 0x00, 0x12, 0x80, 0x22, 0x70, 0xDF, 0xA0, 0x01, 0x00, 0x02, 0x20,
	0xFF, 0xF0, 0x02, 0x00, 0x0A, 0x00, 0x04, 0x00,

	/*列   CC1D0 */
	0x00, 0x20, 0xFE, 0x20, 0x10, 0xA0, 0x1C, 0xA0, 0x24, 0xA0, 0x54, 0xA0, 0x98, 0xA0, 0x08, 0xA0,
	0x10, 0xA0, 0x20, 0x20, 0x40, 0xA0, 0x00, 0x40,

	/*录   CC2BC */
	0x3F, 0x80, 0x00, 0x80, 0x3F, 0x80, 0x00, 0x80, 0xFF, 0xF0, 0x24, 0x40, 0x16, 0x80, 0x0D, 0x00,
	0x34, 0x80, 0xC4, 0x70, 0x14, 0x20, 0x08, 0x00,

	/*面   CC3E6 */
	0x00, 0x20, 0xFF, 0xF0, 0x04, 0x00, 0x7F, 0xE0, 0x49, 0x20, 0x4F, 0x20, 0x49, 0x20, 0x4F, 0x20,
	0x49, 0x20, 0x49, 0x20, 0x7F, 0xE0, 0x40, 0x20,

	/*秒   CC3EB */
	0x18, 0x80, 0xE0, 0x80, 0x22, 0xC0, 0xFA, 0xA0, 0x22, 0x90, 0x62, 0x80, 0x74, 0xB0, 0xA0, 0xA0,
	0x20, 0x40, 0x20, 0x80, 0x23, 0x00, 0x2C, 0x00,

	/*年   CC4EA */
	0x10, 0x40, 0x1F, 0xF0, 0x22, 0x00, 0x42, 0x00, 0x9F, 0xE0, 0x12, 0x00, 0x12, 0x00, 0xFF, 0xF0,
	0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00,

	/*期   CC6DA */
	0x48, 0x10, 0x49, 0xF0, 0xFD, 0x10, 0x49, 0x10, 0x79, 0xF0, 0x49, 0x10, 0x79, 0x10, 0x49, 0xF0,
	0xFD, 0x10, 0x29, 0x10, 0x42, 0x50, 0x84, 0x20,

	/*器   CC6F7 */
	0x79, 0xE0, 0x49, 0x20, 0x79, 0xE0, 0x49, 0x20, 0x04, 0x80, 0xFF, 0xF0, 0x10, 0x80, 0x20, 0x40,
	0xFD, 0xF0, 0x25, 0x20, 0x3D, 0xE0, 0x25, 0x20,

	/*清   CC7E5 */
	0x01, 0x40, 0x4F, 0xE0, 0x21, 0x00, 0x87, 0xC0, 0x41, 0x00, 0x1F, 0xF0, 0x24, 0x40, 0x47, 0xC0,
	0xC4, 0x40, 0x47, 0xC0, 0x44, 0x40, 0x44, 0xC0,

	/*请   CC7EB */
	0x01, 0x20, 0x4F, 0xF0, 0x21, 0x00, 0x07, 0xE0, 0xE1, 0x00, 0x2F, 0xF0, 0x24, 0x20, 0x27, 0xE0,
	0x2C, 0x20, 0x37, 0xE0, 0x24, 0x20, 0x04, 0x60,

	/*取   CC8A1 */
	0x08, 0x00, 0xFC, 0x00, 0x4B, 0xE0, 0x48, 0x20, 0x79, 0x20, 0x49, 0x40, 0x79, 0x40, 0x4C, 0x80,
	0x78, 0x80, 0xC9, 0x40, 0x0A, 0x20, 0x0C, 0x10,

	/*确   CC8B7 */
	0x01, 0x00, 0xF9, 0xE0, 0x22, 0x40, 0x27, 0xF0, 0x4C, 0x90, 0x77, 0xF0, 0xD4, 0x90, 0x57, 0xF0,
	0x54, 0x90, 0x74, 0x90, 0x54, 0xD0, 0x08, 0xA0,

	/*认   CC8CF */
	0x41, 0x00, 0x21, 0x00, 0x11, 0x00, 0x01, 0x00, 0xE1, 0x00, 0x21, 0x00, 0x22, 0x80, 0x2A, 0x80,
	0x32, 0x80, 0x24, 0x40, 0x08, 0x20, 0x30, 0x10,

	/*日   CC8D5 */
	0x00, 0x40, 0x1F, 0xE0, 0x10, 0x40, 0x10, 0x40, 0x10, 0x40, 0x1F, 0xC0, 0x10, 0x40, 0x10, 0x40,
	0x10, 0x40, 0x1F, 0xC0, 0x10, 0x40, 0x00, 0x00,

	/*乳   CC8E9 */
	0x1C, 0x80, 0xE0, 0x80, 0x54, 0x80, 0x54, 0x80, 0xFE, 0x80, 0x04, 0x80, 0x08, 0x80, 0x0E, 0x80,
	0x38, 0x80, 0xC8, 0x90, 0x08, 0x90, 0x30, 0x70,

	/*删   CC9BE */
	0x00, 0x10, 0x77, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0xFF, 0xD0, 0x55, 0x50, 0x55, 0x50,
	0x55, 0x50, 0x55, 0x10, 0x95, 0x50, 0xBB, 0x30,

	/*上   CC9CF */
	0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x40, 0x07, 0xE0, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00,
	0x04, 0x00, 0x04, 0x00, 0x04, 0x20, 0xFF, 0xF0,

	/*时   CCAB1 */
	0x00, 0x40, 0x00, 0x40, 0xF8, 0x40, 0x8F, 0xF0, 0x88, 0x40, 0xFA, 0x40, 0x89, 0x40, 0x89, 0x40,
	0xF8, 0x40, 0x88, 0x40, 0x01, 0x40, 0x00, 0xC0,

	/*是   CCAC7 */
	0x1F, 0x80, 0x10, 0x80, 0x1F, 0x80, 0x10, 0x80, 0x1F, 0x80, 0x00, 0x20, 0xFF, 0xF0, 0x02, 0x00,
	0x13, 0xE0, 0x12, 0x00, 0x2E, 0x00, 0xC3, 0xF0,

	/*数   CCAFD */
	0x94, 0x80, 0x58, 0x80, 0xFD, 0xF0, 0x31, 0x20, 0x5A, 0x20, 0x90, 0x40, 0x21, 0x40, 0xFD, 0x40,
	0x48, 0x80, 0x30, 0x80, 0x29, 0x40, 0xC6, 0x30,

	/*水   CCBAE */
	0x02, 0x00, 0x02, 0x00, 0x02, 0x20, 0xFA, 0x40, 0x0A, 0x80, 0x13, 0x00, 0x12, 0x80, 0x22, 0x80,
	0x22, 0x40, 0x42, 0x30, 0x8A, 0x20, 0x04, 0x00,

	/*所   CCBF9 */
	0x18, 0x60, 0x63, 0x80, 0x42, 0x00, 0x7A, 0x20, 0x4B, 0xF0, 0x4A, 0x40, 0x7A, 0x40, 0x42, 0x40,
	0x42, 0x40, 0x44, 0x40, 0x88, 0x40, 0x90, 0x40,

	/*条   CCCF5 */
	0x08, 0x00, 0x0F, 0xC0, 0x10, 0x80, 0x29, 0x00, 0x46, 0x00, 0x19, 0x80, 0xE2, 0x70, 0x3F, 0xC0,
	0x0A, 0x00, 0x12, 0x80, 0x2A, 0x60, 0x46, 0x20,

	/*无   CCEDE */
	0x00, 0x40, 0x7F, 0xE0, 0x04, 0x00, 0x04, 0x00, 0x04, 0x20, 0xFF, 0xF0, 0x05, 0x00, 0x05, 0x00,
	0x09, 0x10, 0x11, 0x10, 0x21, 0x10, 0xC0, 0xF0,

	/*下   CCFC2 */
	0x00, 0x20, 0xFF, 0xF0, 0x04, 0x00, 0x04, 0x00, 0x06, 0x00, 0x05, 0x00, 0x04, 0xC0, 0x04, 0x40,
	0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00,

	/*小   CD0A1 */
	0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x12, 0x80, 0x12, 0x40, 0x12, 0x20, 0x22, 0x20, 0x42, 0x10,
	0x82, 0x10, 0x02, 0x00, 0x0A, 0x00, 0x06, 0x00,

	/*行   CD0D0 */
	0x10, 0x40, 0x27, 0xE0, 0xD0, 0x00, 0x10, 0x00, 0x2F, 0xF0, 0x60, 0x40, 0xA0, 0x40, 0x20, 0x40,
	0x20, 0x40, 0x20, 0x40, 0x22, 0x40, 0x21, 0x80,

	/*修   CD0DE */
	0x22, 0x00, 0x23, 0xE0, 0x42, 0x20, 0x55, 0x40, 0xD0, 0x80, 0x53, 0x60, 0x54, 0x90, 0x53, 0x40,
	0x54, 0x80, 0x53, 0x20, 0x40, 0xC0, 0x47, 0x00,

	/*选   CD1A1 */
	0x01, 0x00, 0x45, 0x40, 0x27, 0xE0, 0x09, 0x00, 0x01, 0x20, 0xEF, 0xF0, 0x22, 0x80, 0x22, 0x90,
	0x24, 0x90, 0x28, 0x70, 0x50, 0x00, 0x8F, 0xF0,

	/*页   CD2B3 */
	0x00, 0x20, 0xFF, 0xF0, 0x04, 0x00, 0x3F, 0xC0, 0x20, 0x40, 0x24, 0x40, 0x24, 0x40, 0x24, 0x40,
	0x24, 0x40, 0x0B, 0x00, 0x10, 0xC0, 0xE0, 0x20,

	/*一   CD2BB */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/*有   CD3D0 */
	0x04, 0x00, 0x04, 0x20, 0xFF, 0xF0, 0x08, 0x00, 0x1F, 0xC0, 0x30, 0x40, 0x5F, 0xC0, 0x90, 0x40,
	0x1F, 0xC0, 0x10, 0x40, 0x11, 0x40, 0x10, 0x80,

	/*愿   CD4B8 */
	0x3F, 0xF0, 0x22, 0x00, 0x2F, 0xC0, 0x29, 0x40, 0x2A, 0x40, 0x2F, 0xC0, 0x49, 0x40, 0x53, 0x20,
	0x40, 0x10, 0xAB, 0x20, 0x28, 0x50, 0x47, 0xC0,

	/*月   CD4C2 */
	0x1F, 0xC0, 0x10, 0x40, 0x10, 0x40, 0x1F, 0xC0, 0x10, 0x40, 0x10, 0x40, 0x1F, 0xC0, 0x10, 0x40,
	0x10, 0x40, 0x20, 0x40, 0x42, 0x40, 0x81, 0x80,

	/*择   CD4F1 */
	0x27, 0xE0, 0x22, 0x40, 0xFA, 0x80, 0x21, 0x00, 0x26, 0xC0, 0x39, 0x30, 0xE7, 0xC0, 0x21, 0x00,
	0x2F, 0xF0, 0x21, 0x00, 0xA1, 0x00, 0x41, 0x00,

	/*执   CD6B4 */
	0x21, 0x00, 0x21, 0x00, 0xF9, 0x40, 0x27, 0xE0, 0x21, 0x40, 0x31, 0x40, 0x67, 0x40, 0xA1, 0xC0,
	0x22, 0x50, 0x24, 0x50, 0xA8, 0x30, 0x50, 0x10,

	/*中   CD6D0 */
	0x02, 0x00, 0x02, 0x00, 0x02, 0x20, 0x7F, 0xF0, 0x42, 0x20, 0x42, 0x20, 0x7F, 0xE0, 0x42, 0x20,
	0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00,

	/*主   CD6F7 */
	0x08, 0x00, 0x04, 0x40, 0x7F, 0xE0, 0x04, 0x00, 0x04, 0x00, 0x04, 0x80, 0x3F, 0xC0, 0x04, 0x00,
	0x04, 0x00, 0x04, 0x00, 0x04, 0x20, 0xFF, 0xF0,

	/*作   CD7F7 */
	0x12, 0x00, 0x12, 0x20, 0x27, 0xF0, 0x25, 0x00, 0x69, 0x00, 0xB1, 0xF0, 0x21, 0x00, 0x21, 0x00,
	0x21, 0xF0, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00,

	/*钊   CEEC8 */
	0x20, 0x20, 0x20, 0x20, 0x7D, 0x20, 0x81, 0x20, 0x79, 0x20, 0x11, 0x20, 0x11, 0x20, 0xFD, 0x20,
	0x11, 0x20, 0x14, 0x20, 0x18, 0x20, 0x10, 0x60

};
