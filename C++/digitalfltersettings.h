#ifndef DIGITALFLTERSETTINGS_H
#define DIGITALFLTERSETTINGS_H

/*
 * Файл содержит наборы коэффициентов для цифровых фильтров
 * сгенерированных на сайте http://www-users.cs.york.ac.uk/~fisher/mkfilter
 */

/*
 * You specified the following parameters:
 * filtertype  =   Chebyshev
 * passtype    =   Lowpass
 * ripple  =   -2
 * order   =   10
 * samplerate  =   8000
 * corner1 =   25
 * corner2 =
 * adzero  =
 * logmin  =
 */
static const int    Cheb_LP_10_8000_25_PolesCount = 10;
static const double Cheb_LP_10_8000_25_GAIN = 4.309984576e+16;
static const int    Cheb_LP_10_8000_25_XCoef[11] {1, 10, 45, 120, 210, 252, 210, 120, 45, 10, 1 };
static const double Cheb_LP_10_8000_25_YCoef[10] {-0.9864717669, 9.8772023238, -44.5046236731, 118.8343286800, -208.2367624457, 250.2219905499, -208.8047844976, 119.4835201273, -44.8698157896, 9.9854164919};

/*
 * You specified the following parameters:
 * filtertype	=	Chebyshev
 * passtype	=	Lowpass
 * ripple	=	-5
 * order	=	5
 * samplerate	=	8000
 * corner1	=	75
 * corner2	=
 * adzero	=
 * logmin	=
 */
static const int    Cheb_LP_5_8000_75_PolesCount = 5;
static const double Cheb_LP_5_8000_75_GAIN = 1.074222791e+09;
static const int    Cheb_LP_5_8000_75_XCoef[6] { 1, 5, 10, 10, 5, 1};
static const double Cheb_LP_5_8000_75_YCoef[5] { 0.9759717316, -4.8993488905, 9.8421429565, -9.8901219184, 4.9713560910};

/*
 * You specified the following parameters:
 * filtertype  = Chebyshev
 * passtype  = Lowpass
 * ripple  = -5
 * order = 5
 * samplerate  = 8000
 * corner1 = 50
 * corner2 =
 * adzero  =
 * logmin  =
 */
static const int    Cheb_LP_5_8000_50_PolesCount = 5;
static const double Cheb_LP_5_8000_50_GAIN = 8.126014038e+09;
static const int    Cheb_LP_5_8000_50_XCoef[6] { 1, 5, 10, 10, 5, 1};
static const double Cheb_LP_5_8000_50_YCoef[5] { 0.9839161993,-4.9336338867, 9.8973822260,-9.9295267435, 4.9818622010};

/*
 * You specified the following parameters:
 * filtertype	=	Chebyshev
 * passtype	=	Lowpass
 * ripple	=	-5
 * order	=	5
 * samplerate	=	8000
 * corner1	=	25
 * corner2	=
 * adzero	=
 * logmin	=
 */
static const int    Cheb_LP_5_8000_25_PolesCount = 5;
static const double Cheb_LP_5_8000_25_GAIN = 2.590145688e+11;
static const int    Cheb_LP_5_8000_25_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Cheb_LP_5_8000_25_YCoef[5] { 0.9919254678,-4.9671906261, 9.9500162272,-9.9661623940, 4.9914113250};

/*
 * You specified the following parameters:
 * filtertype	=	Chebyshev
 * passtype	=	Highpass
 * ripple	=	-2
 * order	=	10
 * samplerate	=	8000
 * corner1	=	25
 * corner2	=
 * adzero	=
 * logmin	=
 */
static const int    Cheb_HP_10_8000_25_PolesCount = 10;
static const double Cheb_HP_10_8000_25_GAIN = 4.309984576e+16;
static const int    Cheb_HP_10_8000_25_XCoef[11] { 1, -10, 45, -120, 210, -252, 210, -120, 45, -10, 1};
static const double Cheb_HP_10_8000_25_YCoef[10] { -0.8673382807,  8.7903157445,-40.0976959701,108.4114032593,-192.3898616134,234.1601393448,-197.9519135879,114.7694245720,-43.6753868869,  9.8509134185};

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	10
 * samplerate	=	8000
 * corner1	=	25
 * corner2	=
 * adzero	=
 * logmin	=
 */
static const int    Butt_LP_10_8000_25_PolesCount = 10;
static const double Butt_LP_10_8000_25_GAIN = 4.135989664e+16;
static const int    Butt_LP_10_8000_25_XCoef[11] { 1, 10, 45,120,210,252,210,120, 45, 10,  1};
static const double Butt_LP_10_8000_25_YCoef[10] { -0.8820397389,  8.9311069502,-40.6951295322,109.8862414274,-194.7247103026,236.6189843118,-199.6747802866,115.5440727746,-43.8782302142,  9.8744846105 };

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	75
 * corner2	=
 * adzero	=
 * logmin	=
 */
static const int    Butt_LP_5_8000_75_PolesCount = 5;
static const double Butt_LP_5_8000_75_GAIN = 4.956399279e+07;
static const int    Butt_LP_5_8000_75_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_75_YCoef[5] { 0.8264183037,-4.2896168515, 8.9094018223,-9.2555918146, 4.8093878944};

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	50
 * corner2	=
 * adzero	=
 * logmin	=
 */
static const int    Butt_LP_5_8000_50_PolesCount = 5;
static const double Butt_LP_5_8000_50_GAIN = 3.648957062e+08;
static const int    Butt_LP_5_8000_50_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_50_YCoef[5] { 0.8806542456,-4.5151827537, 9.2613322417,-9.4997261105, 4.8729222892};

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	25
 * corner2	=
 * adzero	=
 * logmin	=
 */
static const int    Butt_LP_5_8000_25_PolesCount = 5;
static const double Butt_LP_5_8000_25_GAIN = 1.131692270e+10;
static const int    Butt_LP_5_8000_25_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_25_YCoef[5] { 0.9384353538,-4.7518047150, 9.6247640850,-9.7478549782, 4.9364602516};

/*
 * You specified the following parameters:
 * filtertype	=	Bessel
 * passtype	=	Lowpass
 * ripple	=
 * order	=	10
 * samplerate	=	8000
 * corner1	=	25
 * corner2	=
 * adzero	=
 * logmin	=
 */
static const int    Bess_LP_10_8000_25_PolesCount = 10;
static const double Bess_LP_10_8000_25_GAIN = 2.547652649e+16;
static const int    Bess_LP_10_8000_25_XCoef[11] { 1, 10, 45,120,210,252,210,120, 45, 10, 1};
static const double Bess_LP_10_8000_25_YCoef[10] { -0.7402834694,  7.6260336569,-35.3546738149, 97.1373603213,-175.1581683623,216.5973812636,-186.0155376845,109.5530168921,-42.3452672281,  9.7001384252};

/*
 * You specified the following parameters:
 * filtertype  = Bessel
 * passtype  = Lowpass
 * ripple  =
 * order = 5
 * samplerate  = 8000
 * corner1 = 75
 * corner2 =
 * adzero  =
 * logmin  =
 */
static const int    Bess_LP_5_8000_75_PolesCount = 5;
static const double Bess_LP_5_8000_75_GAIN = 4.815181659e+06;
static const int    Bess_LP_5_8000_75_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Bess_LP_5_8000_75_YCoef[5] { 0.6948938597,-3.7303175778, 8.0168438249,-8.6220465424, 4.6406197899};

/*
 * You specified the following parameters:
 * filtertype	=	Bessel
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	50
 * corner2	=
 * adzero	=
 * logmin	=
 */
static const int    Bess_LP_5_8000_50_PolesCount = 5;
static const double Bess_LP_5_8000_50_GAIN = 3.446172299e+07;
static const int    Bess_LP_5_8000_50_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Bess_LP_5_8000_50_YCoef[5] { 0.7845344145,-4.1145387828, 8.6348898536,-9.0642450192, 4.7593586053};

/*
 * You specified the following parameters:
 * filtertype	=	Bessel
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	25
 * corner2	=
 * adzero	=
 * logmin	=
 */
static const int    Bess_LP_5_8000_25_PolesCount = 5;
static const double Bess_LP_5_8000_25_GAIN = 1.038745219e+09;
static const int    Bess_LP_5_8000_25_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Bess_LP_5_8000_25_YCoef[5] { 0.8857392822,-4.5365929474, 9.2951376804,-9.5234498853, 4.8791658393};

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	475
 * corner2	=
 * adzero	=
 * logmin	=
 */
static const int    Butt_LP_5_8000_475_PolesCount = 5;
static const double Butt_LP_5_8000_475_GAIN = 7.671764535e+03;
static const int    Butt_LP_5_8000_475_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_475_YCoef[5] { 0.2964092376, -1.8393091968, 4.6177641132, -5.8737332193, 3.7946979258 };

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	525
 * corner2	=
 * adzero	=
 * logmin	=
 * Results
*/
static const int    Butt_LP_5_8000_525_PolesCount = 5;
static const double Butt_LP_5_8000_525_GAIN = 4.899486538e+03;
static const int    Butt_LP_5_8000_525_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_525_YCoef[5] { 0.2602298984, -1.6477036806, 4.2302624550, -5.5175999892, 3.6682800197 };

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	575
 * corner2	=
 * adzero	=
 * logmin	=
 * Results
*/
static const int    Butt_LP_5_8000_575_PolesCount = 5;
static const double Butt_LP_5_8000_575_GAIN = 3.271477041e+03;
static const int    Butt_LP_5_8000_575_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_575_YCoef[5] { 0.2283143973, -1.4744588347, 3.8699686797, -5.1755944217, 3.5419886650 };

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	625
 * corner2	=
 * adzero	=
 * logmin	=
 * Results
*/
static const int    Butt_LP_5_8000_625_PolesCount = 5;
static const double Butt_LP_5_8000_625_GAIN = 2.266623674e+03;
static const int    Butt_LP_5_8000_625_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_625_YCoef[5] { 0.2001656325, -1.3179281623, 3.5353273147, -4.8475141149, 3.4158314151 };

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	675
 * corner2	=
 * adzero	=
 * logmin	=
 * Results
*/
static const int    Butt_LP_5_8000_675_PolesCount = 5;
static const double Butt_LP_5_8000_675_GAIN = 1.620038226e+03;
static const int    Butt_LP_5_8000_675_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_675_YCoef[5] { 0.1753454112, -1.1766078029, 3.2248532349, -4.5331582691, 3.2898148055 };

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	725
 * corner2	=
 * adzero	=
 * logmin	=
 * Results
*/
static const int    Butt_LP_5_8000_725_PolesCount = 5;
static const double Butt_LP_5_8000_725_GAIN = 1.189034425e+03;
static const int    Butt_LP_5_8000_725_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_725_YCoef[5] { 0.1534671808, -1.0491243371, 2.9371286259, -4.2323283994, 3.1639443363 };

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	775
 * corner2	=
 * adzero	=
 * logmin	=
 * Results
*/
static const int    Butt_LP_5_8000_775_PolesCount = 5;
static const double Butt_LP_5_8000_775_GAIN = 8.928925551e+02;
static const int    Butt_LP_5_8000_775_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_775_YCoef[5] { 0.1341897008, -0.9342236620, 2.6707999256, -3.9448290073, 3.0382244643 };

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	825
 * corner2	=
 * adzero	=
 * logmin	=
 * Results
*/
static const int    Butt_LP_5_8000_825_PolesCount = 5;
static const double Butt_LP_5_8000_825_GAIN = 6.839920516e+02;
static const int    Butt_LP_5_8000_825_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_825_YCoef[5] { 0.1172115264, -0.8307608524, 2.4245747623, -3.6704682096, 2.9126586038 };

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	875
 * corner2	=
 * adzero	=
 * logmin	=
 * Results
*/
static const int    Butt_LP_5_8000_875_PolesCount = 5;
static const double Butt_LP_5_8000_875_GAIN = 5.331999278e+02;
static const int    Butt_LP_5_8000_875_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_875_YCoef[5] { 0.1022661938, -0.7376909254, 2.1972189077, -3.4090583234, 2.7872491354 };

/*
 * You specified the following parameters:
 * filtertype	=	Butterworth
 * passtype	=	Lowpass
 * ripple	=
 * order	=	5
 * samplerate	=	8000
 * corner1	=	925
 * corner2	=
 * adzero	=
 * logmin	=
*/
static const int    Butt_LP_5_8000_925_PolesCount = 5;
static const double Butt_LP_5_8000_925_GAIN = 4.221181912e+02;
static const int    Butt_LP_5_8000_925_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_925_YCoef[5] { 0.0891180104, -0.6540604341, 1.9875532585, -3.1604164084, 2.6619974216 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	486
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_486_PolesCount = 5;
static const double Butt_LP_5_8000_486_GAIN = 6.921324981e+03;
static const int    Butt_LP_5_8000_486_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_486_YCoef[5] { 0.2880563379, -1.7954914205, 4.5300975568, -5.7941614145, 3.7668755482 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	536
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_536_PolesCount = 5;
static const double Butt_LP_5_8000_536_GAIN = 4.467156715e+03;
static const int    Butt_LP_5_8000_536_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_536_YCoef[5] { 0.2528609789, -1.6080742447, 4.1487187799, -5.4411536916, 3.6404847844 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	586
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_586_PolesCount = 5;
static const double Butt_LP_5_8000_586_GAIN = 3.008885560e+03;
static const int    Butt_LP_5_8000_586_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_586_YCoef[5] { 0.2218146338, -1.4386426104, 3.7941994930, -5.1022290031, 3.5142223198 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	636
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_636_PolesCount = 5;
static const double Butt_LP_5_8000_636_GAIN = 2.099949863e+03;
static const int    Butt_LP_5_8000_636_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_636_YCoef[5] { 0.1944338378, -1.2855825050, 3.4649999585, -4.7771852363, 3.3880954860 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	686
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_686_PolesCount = 5;
static const double Butt_LP_5_8000_686_GAIN = 1.510235133e+03;
static const int    Butt_LP_5_8000_686_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_686_YCoef[5] { 0.1702923474, -1.1474197728, 3.1596501213, -4.4658220411, 3.2621105917 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	736
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_736_PolesCount = 5;
static const double Butt_LP_5_8000_736_GAIN = 1.114356230e+03;
static const int    Butt_LP_5_8000_736_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_736_YCoef[5] { 0.1490140915, -1.0228081626, 2.8767465653, -4.1679415336, 3.1362729079 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	786
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_786_PolesCount = 5;
static const double Butt_LP_5_8000_786_GAIN = 8.406840723e+02;
static const int    Butt_LP_5_8000_786_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_786_YCoef[5] { 0.1302670318, -0.9105184279, 2.6149494528, -3.8833489581, 3.0105866618 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	836
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_836_PolesCount = 5;
static const double Butt_LP_5_8000_836_GAIN = 6.466032874e+02;
static const int    Butt_LP_5_8000_836_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_836_YCoef[5] { 0.1137578100, -0.8094283930, 2.3729794642, -3.6118533067, 2.8850550391 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	886
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_886_PolesCount = 5;
static const double Butt_LP_5_8000_886_GAIN = 5.058506610e+02;
static const int    Butt_LP_5_8000_886_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_886_YCoef[5] { 0.0992270737, -0.7185139069, 2.1496147563, -3.3532678951, 2.7596801950 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	936
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_936_PolesCount = 5;
static const double Butt_LP_5_8000_936_GAIN = 4.017330166e+02;
static const int    Butt_LP_5_8000_936_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_936_YCoef[5] { 0.0864453886, -0.6368406089, 1.9436879524, -3.1074108946, 2.6344632705 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	464
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_464_PolesCount = 5;
static const double Butt_LP_5_8000_464_GAIN = 8.525974984e+03;
static const int    Butt_LP_5_8000_464_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_464_YCoef[5] { 0.3049955284, -1.8841022160, 4.7068260727, -5.9539986401, 3.8225260186 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	514
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_514_PolesCount = 5;
static const double Butt_LP_5_8000_514_GAIN = 5.385199161e+03;
static const int    Butt_LP_5_8000_514_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_514_YCoef[5] { 0.2678049302, -1.6882211748, 4.3131227101, -5.5947300624, 3.6960813839 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	564
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_564_PolesCount = 5;
static const double Butt_LP_5_8000_564_GAIN = 3.563326803e+03;
static const int    Butt_LP_5_8000_564_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_564_YCoef[5] { 0.2349962453, -1.5110834781, 3.9469791730, -5.2496338168, 3.5697615047 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	614
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_614_PolesCount = 5;
static const double Butt_LP_5_8000_614_GAIN = 2.450201250e+03;
static const int    Butt_LP_5_8000_614_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_614_YCoef[5] { 0.2060583310, -1.3510094985, 3.6068241091, -4.9185072485, 3.4435741552 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	664
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_664_PolesCount = 5;
static const double Butt_LP_5_8000_664_GAIN = 1.740051787e+03;
static const int    Butt_LP_5_8000_664_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_664_YCoef[5] { 0.1805406939, -1.2064650812, 3.2911571762, -4.6011491427, 3.3175260965 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	714
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_714_PolesCount = 5;
static const double Butt_LP_5_8000_714_GAIN = 1.270119434e+03;
static const int    Butt_LP_5_8000_714_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_714_YCoef[5] { 0.1580459941, -1.0760491000, 2.9985460136, -4.2973604463, 3.1916230576 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	764
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_764_PolesCount = 5;
static const double Butt_LP_5_8000_764_GAIN = 9.492557472e+02;
static const int    Butt_LP_5_8000_764_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_764_YCoef[5] { 0.1382235222, -0.9584821056, 2.7276231865, -4.0069449483, 3.0658697249 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	814
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_814_PolesCount = 5;
static const double Butt_LP_5_8000_814_GAIN = 7.241536858e+02;
static const int    Butt_LP_5_8000_814_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_814_YCoef[5] { 0.1207635145, -0.8525959763, 2.4770831235, -3.7297099183, 2.9402697418 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	864
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_864_PolesCount = 5;
static const double Butt_LP_5_8000_864_GAIN = 5.624472902e+02;
static const int    Butt_LP_5_8000_864_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_864_YCoef[5] { 0.1053921922, -0.7573244911, 2.2456790649, -3.4654667013, 2.8148257150 };

/*
You specified the following parameters:
filtertype	=	Butterworth
passtype	=	Lowpass
ripple	=
order	=	5
samplerate	=	8000
corner1	=	914
corner2	=
adzero	=
logmin	=
Results
*/
static const int    Butt_LP_5_8000_914_PolesCount = 5;
static const double Butt_LP_5_8000_914_GAIN = 4.438321829e+02;
static const int    Butt_LP_5_8000_914_XCoef[6] { 1, 5,10,10, 5, 1};
static const double Butt_LP_5_8000_914_YCoef[5] { 0.0918674264, -0.6716947465, 2.0322200370, -3.2140312695, 2.6895392294 };



#endif // DIGITALFLTERSETTINGS_H
