﻿#include "test_dynamic_block_matrix.h"
#include <iostream>
#include <aris.h>
#include <aris_dynamic_cell.h>

using namespace aris::dynamic;

const double error = 1e-10;

void test_block_multiply()
{
	double mat[]{ -0.8147,-0.2785,-0.9572,-0.7922,-0.6787,-0.7060,0,
		0.9058,0.5469,0.4854,0.9595,0.7577,-0.0318,0,
		0.1270,0.9575,0.8003,0.6557,0.7431,-0.2769,0,
		0.9134,0.9649,0.1419,0.0357,0.3922,-0.0462,0,
		0.6324,0.1576,0.4218,0.8491,0.6555,-0.0971,0,
		0.0975,0.9706,0.9157,0.9340,0.1712,-0.8235,0 };

	const BlockData block_mat{ { mat + 0, false },{ mat + 3, false },{ mat + 5, false } ,
			{ mat + 7, false },{ mat + 10, false },{ mat + 12, false } ,
			{ mat + 21, false },{ mat + 24, false },{ mat + 26, false } };

	BlockData block_mat_result;
	block_mat_result.resize(9);

	s_blk_map({ 1,2,3 }, { 3,2,1 }, mat, 7, block_mat_result, 3);
	if (!std::equal(block_mat_result.begin(), block_mat_result.end(), block_mat.begin(), [](const BlockNode &n1, const BlockNode &n2)->bool {return (n1.data == n2.data) && (n1.is_zero == n2.is_zero); }))
		std::cout << "\"s_blk_map\" failed" << std::endl;

	s_blk_map({ 1,2,3 }, { 3,2,2 }, mat, block_mat_result);
	if (!std::equal(block_mat_result.begin(), block_mat_result.end(), block_mat.begin(), [](const BlockNode &n1, const BlockNode &n2)->bool {return (n1.data == n2.data) && (n1.is_zero == n2.is_zero); }))
		std::cout << "\"s_blk_map\" failed" << std::endl;

	if (!s_is_equal(s_blk_norm_fro({ 1,2,3 }, { 3,2,1 }, block_mat, BlockStride{ 3,1,7,1 }), 3.97526237121526, error)) std::cout << "\"s_blk_norm_fro\" failed" << std::endl;

	if (!s_is_equal(s_blk_norm_1({ 1,2,3 }, { 3,2,1 }, block_mat, BlockStride{ 3,1,7,1 }), 4.2262, error)) std::cout << "\"s_blk_norm_1\" failed" << std::endl;

	if (!s_is_equal(s_blk_norm_inf({ 1,2,3 }, { 3,2,1 }, block_mat, BlockStride{ 3,1,7,1 }), 4.2273, error)) std::cout << "\"s_blk_norm_inf\" failed" << std::endl;

	const double alpha = 1.2;
	double A[]{ 0.083469814858914,0.0604711791698936,0.291984079961715,0.372409740055537,0.0526769976807926,0.417744104316662,0.698105520180308,0.032600820530528,0.460725937260412,
		0.133171007607162,0.399257770613576, 0.43165117024872,0.198118402542975,0.737858095516997,0.983052466469856,0.666527913402587, 0.56119979270966, 0.98163795097075,
		0.173388613119006,0.526875830508296,0.015487125636019,0.489687638016024,0.269119426398556,0.301454948712065,0.178132454400338, 0.88186650045181,0.156404952226563,
		0.390937802323736,0.416799467930787,0.984063724379154,0.339493413390758,0.422835615008808,0.701098755900926,0.128014399720173,0.669175304534394,0.855522805845911,
		0.83137974283907,0.656859890973707,0.167168409914656,0.951630464777727,0.547870901214845,0.666338851584426,0.999080394761361,0.190433267179954,0.644764536870088,
		0.80336439160244,0.627973359190104,0.106216344928664,0.920332039836564,0.942736984276934,0.539126465042857,0.171121066356432,0.368916546063895,0.376272210278832 };
	double AT[]{ 0.083469814858914,0.133171007607162,0.173388613119006,0.390937802323736, 0.83137974283907, 0.80336439160244,
		0.0604711791698936,0.399257770613576,0.526875830508296,0.416799467930787,0.656859890973707,0.627973359190104,
		0.291984079961715, 0.43165117024872,0.015487125636019,0.984063724379154,0.167168409914656,0.106216344928664,
		0.372409740055537,0.198118402542975,0.489687638016024,0.339493413390758,0.951630464777727,0.920332039836564,
		0.0526769976807926,0.737858095516997,0.269119426398556,0.422835615008808,0.547870901214845,0.942736984276934,
		0.417744104316662,0.983052466469856,0.301454948712065,0.701098755900926,0.666338851584426,0.539126465042857,
		0.698105520180308,0.666527913402587,0.178132454400338,0.128014399720173,0.999080394761361,0.171121066356432,
		0.032600820530528, 0.56119979270966, 0.88186650045181,0.669175304534394,0.190433267179954,0.368916546063895,
		0.460725937260412, 0.98163795097075,0.156404952226563,0.855522805845911,0.644764536870088,0.376272210278832 };
	double B[]{ 0.32514568182056,0.440085139001721,0.676122303863752,0.344462411301042,0.424349039815375,
		0.105629203329022,0.527142741760652,0.289064571674477,0.780519652731358,0.460916366028964,
		0.610958658746201,0.457424365687674,0.671808165414215,0.675332065747,0.770159728608609,
		0.778802241824093,0.875371598604185,0.695140499551737,0.00671531431847749,0.322471807186779,
		0.423452918962738,0.518052108361104,0.0679927684700106,0.602170487581795,0.784739294760742,
		0.0908232857874395,0.943622624548388,0.254790156597005,0.386771194520985,0.471357153710612,
		0.266471490779072,0.637709098072174,0.224040030824219,0.915991244131425,0.0357627332691179,
		0.153656717591307,0.957693939841583,0.667832727013717,0.00115105712910724,0.175874415683531,
		0.281005302533871, 0.24070703548016,0.844392156527205,0.462449159242329,0.721758033391102 };
	double BT[]{ 0.32514568182056,0.105629203329022,0.610958658746201,0.778802241824093,0.423452918962738,0.0908232857874395,0.266471490779072,0.153656717591307,0.281005302533871,
		0.440085139001721,0.527142741760652,0.457424365687674,0.875371598604185,0.518052108361104,0.943622624548388,0.637709098072174,0.957693939841583,0.24070703548016,
		0.676122303863752,0.289064571674477,0.671808165414215,0.695140499551737,0.0679927684700106,0.254790156597005,0.224040030824219,0.667832727013717,0.844392156527205,
		0.344462411301042,0.780519652731358,  0.675332065747,0.00671531431847749,0.602170487581795,0.386771194520985,0.915991244131425,0.00115105712910724,0.462449159242329,
		0.424349039815375,0.460916366028964,0.770159728608609,0.322471807186779,0.784739294760742,0.471357153710612,0.0357627332691179,0.175874415683531,0.721758033391102 };
	double C[]{ 0.882699220389462,1.53696035254701,1.20617784639246,1.32148852911613,1.00973535379553,
		1.44490982798386,3.14862260940081,2.28680308612416,2.54000934334887,2.51030105404234,
		0.871122945877781,2.20946761947791,1.47636028538785,0.999872211710309,1.11389732784129,
		1.65682740032538,2.94813131784912,2.68725848495219,2.16628320911793,2.62740013735909,
		1.9521547101672,3.50893087374696,2.62828481759543,2.71952708284136,2.36977862102099,
		1.76538308227268,3.08892358329822,2.23971174415062,1.95216979243096,2.34543889613871 };
	double C2[]{ 1.76539844077892,3.07392070509402,2.41235569278492,2.64297705823226,2.01947070759106,
		2.88981965596772,6.29724521880162,4.57360617224832,5.08001868669774,5.02060210808468,
		1.74224589175556,4.41893523895582,2.9527205707757,1.99974442342062,2.22779465568258,
		3.31365480065076,5.89626263569824,5.37451696990438,4.33256641823586,5.25480027471818,
		3.9043094203344,7.01786174749392,5.25656963519086,5.43905416568272,4.73955724204198,
		3.53076616454536,6.17784716659644,4.47942348830124,3.90433958486192,4.69087779227742 };
	double C3[]{ 1.05923906446735,1.84435242305641,1.44741341567095,1.58578623493936,1.21168242455464,
		1.73389179358063,3.77834713128097,2.74416370334899,3.04801121201864,3.01236126485081,
		1.04534753505334,2.65136114337349,1.77163234246542,1.19984665405237,1.33667679340955,
		1.98819288039046,3.53775758141894,3.22471018194263,2.59953985094152,3.15288016483091,
		2.34258565220064,4.21071704849635,3.15394178111452,3.26343249940963,2.84373434522519,
		2.11845969872722,3.70670829995786,2.68765409298074,2.34260375091715,2.81452667536645 };
	double C4[]{ 2.11847812893471,3.68870484611282,2.8948268313419,3.17157246987871,2.42336484910927,
		3.46778358716126,7.55669426256194,5.48832740669798,6.09602242403729,6.02472252970162,
		2.09069507010667,5.30272228674698,3.54326468493084,2.39969330810474,2.6733535868191,
		3.97638576078091,7.07551516283789,6.44942036388526,5.19907970188303,6.30576032966182,
		4.68517130440128,8.4214340969927,6.30788356222903,6.52686499881926,5.68746869045038,
		4.23691939745443,7.41341659991573,5.37530818596149,4.6852075018343,5.6290533507329 };

	double result[6*10];
	BlockSize blk_m{ 2,4 }, blk_n{ 3,2 }, blk_k{ 1,3,5 };
	BlockData blk_A(6), blk_B(6), blk_C(4);

	s_blk_map(blk_m, blk_k, A, blk_A);
	s_blk_map(blk_k, blk_n, B, blk_B);
	s_blk_map(blk_m, blk_n, result, blk_C);
	s_blk_mm(blk_m, blk_n, blk_k, blk_A, blk_B, blk_C);
	if (!s_is_equal(30, result, C, error))std::cout << "\"s_blk_mm\" failed" << std::endl;

	s_blk_mma(blk_m, blk_n, blk_k, blk_A, blk_B, blk_C);
	if (!s_is_equal(30, result, C2, error))std::cout << "\"s_blk_mma\" failed" << std::endl;

	s_blk_mm(blk_m, blk_n, blk_k, alpha, blk_A, blk_B, blk_C);
	if (!s_is_equal(30, result, C3, error))std::cout << "\"s_blk_mm\" failed" << std::endl;

	s_blk_mma(blk_m, blk_n, blk_k, alpha, blk_A, blk_B, blk_C);
	if (!s_is_equal(30, result, C4, error))std::cout << "\"s_blk_mma\" failed" << std::endl;

	s_blk_map(blk_k, blk_m, AT, blk_A);
	s_blk_map(blk_n, blk_k, BT, blk_B);
	s_blk_map(blk_m, blk_n, result, blk_C);
	s_blk_mm(blk_m, blk_n, blk_k, blk_A, T(BlockStride{ 2,1,6,1 }), blk_B, T(BlockStride{ 3,1,9,1 }), blk_C, BlockStride{ 2,1,5,1 });
	if (!s_is_equal(30, result, C, error))std::cout << "\"s_blk_mm\" failed" << std::endl;

	s_blk_mma(blk_m, blk_n, blk_k, blk_A, T(BlockStride{ 2,1,6,1 }), blk_B, T(BlockStride{ 3,1,9,1 }), blk_C, BlockStride{ 2,1,5,1 });
	if (!s_is_equal(30, result, C2, error))std::cout << "\"s_blk_mma\" failed" << std::endl;

	s_blk_mm(blk_m, blk_n, blk_k, alpha, blk_A, T(BlockStride{ 2,1,6,1 }), blk_B, T(BlockStride{ 3,1,9,1 }), blk_C, BlockStride{ 2,1,5,1 });
	if (!s_is_equal(30, result, C3, error))std::cout << "\"s_blk_mm\" failed" << std::endl;

	s_blk_mma(blk_m, blk_n, blk_k, alpha, blk_A, T(BlockStride{ 2,1,6,1 }), blk_B, T(BlockStride{ 3,1,9,1 }), blk_C, BlockStride{ 2,1,5,1 });
	if (!s_is_equal(30, result, C4, error))std::cout << "\"s_blk_mma\" failed" << std::endl;
}
void test_block_llt()
{
	double A[]{ 1.82553083943141,1.42060601118548,1.36736238745112,1.50658906468564,1.86464891726001,1.04079482779702,
		1.42060601118548,2.10941693872417,1.92463386848915,1.23889223270807,2.23186828169132,1.22211204078486,
		1.36736238745112,1.92463386848915,2.06653199450749,1.37659815598197,2.07988145626914,1.30113287432829,
		1.50658906468564,1.23889223270807,1.37659815598197,1.69212820994619,1.67619205287543,0.914095057763804,
		1.86464891726001,2.23186828169132,2.07988145626914,1.67619205287543, 3.0881251584706,1.69495025317372,
		1.04079482779702,1.22211204078486,1.30113287432829,0.914095057763804,1.69495025317372,1.17872570447206 };

	double A_t[]{ 1.82553083943141,1.42060601118548,1.36736238745112,1.50658906468564,1.86464891726001,1.04079482779702,0.0,
		1.42060601118548,2.10941693872417,1.92463386848915,1.23889223270807,2.23186828169132,1.22211204078486,0.0,
		1.36736238745112,1.92463386848915,2.06653199450749,1.37659815598197,2.07988145626914,1.30113287432829,0.0,
		1.50658906468564,1.23889223270807,1.37659815598197,1.69212820994619,1.67619205287543,0.914095057763804,0.0,
		1.86464891726001,2.23186828169132,2.07988145626914,1.67619205287543, 3.0881251584706,1.69495025317372,0.0,
		1.04079482779702,1.22211204078486,1.30113287432829,0.914095057763804,1.69495025317372,1.17872570447206,0.0 };
	
	double b[]{ 0.765516788149002,0.709364830858073,
		0.795199901137063,0.754686681982361,
		0.186872604554379,0.276025076998578,
		0.489764395788231,0.679702676853675,
		0.445586200710899,0.655098003973841,
		0.646313010111265,0.162611735194631 };

	double b_t[]{ 0.765516788149002,0.709364830858073,0.0,0.0,
		0.795199901137063,0.754686681982361,0.0,0.0,
		0.186872604554379,0.276025076998578,0.0,0.0,
		0.489764395788231,0.679702676853675,0.0,0.0,
		0.445586200710899,0.655098003973841,0.0,0.0,
		0.646313010111265,0.162611735194631,0.0,0.0 };

	double bT[]{ 0.765516788149002,0.795199901137063,0.186872604554379,0.489764395788231,0.445586200710899,0.646313010111265,
		0.709364830858073,0.754686681982361,0.276025076998578,0.679702676853675,0.655098003973841,0.162611735194631 };

	double llt[]{ 1.35112206681388,1.05142684445637,1.01201987669074,1.11506510158506,1.38007435675823,0.770318873002606,
		1.05142684445637,1.00195734913254,0.858887859606139,0.0663529756457487,0.779295701883798,0.411372898532454,
		1.01201987669074,0.858887859606139,0.551959607499983,0.346294079395723,0.025166983849247,0.30478983036659,
		1.11506510158506,0.0663529756457487,0.346294079395723,0.569592593325883,0.135000937041167, - 0.136419197085494,
		1.38007435675823,0.779295701883798,0.025166983849247,0.135000937041167,0.746565139312267,0.431332592509531,
		0.770318873002606,0.411372898532454,0.30478983036659,-0.136419197085494,0.431332592509531,0.344313858756401 };

	double inv_l[]{ 0.740125577519527,0,0,0,0,0,
		-0.77666769064225,0.998046474598712,0,0,0,0,
		-0.148473446503069, -1.55303031002242,1.81172677567722,0,0,0,
		-1.26816697217082,0.827928336123375, -1.10147193494276,1.75564080663506,0,0,
		-0.323125426175609, -1.13916294185447,0.138104552985304, -0.31747149916724,1.3394678472681,0,
		-0.69415520561586,1.93742418585395, -2.21317495390761,1.09330166190531, -1.67799269315532,2.90432689410723 };

	double inv_l_dot_b[]{ 0.566578554929674,0.525019055110873,
		0.19909430193153,0.202271637373723,
		-1.01006636357342,-0.777291110197726,
		0.341580853217506,0.614513319403422,
		-0.686050087570733,-0.389108108915027,
		2.26054438577134,0.474995191389852 };
	double inv_u_dot_b[]{-1.29249793785305,-1.28863719172842,
		1.65350463041262,0.456066717040007,
		-1.56976591868037,-0.518007602446926,
		1.42500452780045,1.16312249077394,
		-0.487660119419236,0.604621409654585,
		1.87710425727744,0.472277635823185 };


	double B[]{ 0.854463601335834,0.915158806735392,0.81779406393944,0,0,0,
		0.915158806735392,1.51973084603713,1.08911106493401,0,0,0,
		0.81779406393944,1.08911106493401,1.00718816511107,0,0,0,
		0,0,0,1.16505945742745,0.55867090856838,1.06119850911405,
		0,0,0,0.55867090856838,0.321956437380287,0.442097312015519,
		0,0,0,1.06119850911405,0.442097312015519,1.05023839402297 };

	double B_llt[]{ 0.924372003760301,0.990033020269512,0.88470232829715,0,0,0,
		0.990033020269512,0.734551199585949,0.290281394858118,0,0,0,
		0.88470232829715,0.290281394858118,0.374468512983265,0,0,0,
		0,0,0,1.07937920001613,0.517585394048759,0.983156344960322,
		0,0,0,0.517585394048759,0.232511929258862, - 0.287168286010691,
		0,0,0,0.983156344960322, - 0.287168286010691,0.0342982637594407 };

	double C[]{ 1.09756159899368,0.494892128610864,0,0,0,0.599982575914901,
		0.494892128610864,0.564212545623307,0,0,0,0.200848874880563,
		0,0,0.979041348469538,0.638782936554467,0.663380272499309,0,
		0,0,0.638782936554467,0.791575910209436,0.454993751889092,0,
		0,0,0.663380272499309,0.454993751889092,0.470703623796929,0,
		0.599982575914901,0.200848874880563,0,0,0,1.00673482446645 };

	double C_llt[]{ 1.04764574117097,0.472384995387576,0,0,0,0.572696048231236,
		0.472384995387576,0.584007672685888,0,0,0, -0.119320598822187,
		0,0,0.989465183050691,0.645584046307713,0.670443269619648,0,
		0,0,0.645584046307713,0.612206786439351,0.0362071665314066,0,
		0,0,0.670443269619648,0.0362071665314066,0.141061997399768,0,
		0.572696048231236, -0.119320598822187,0,0,0,0.815178910119423 };
	double result_llt[36], result_x[12];

	BlockData A_blk(3*3), L_blk(3*3), b_blk(3*2), x_blk(3*2);
	BlockSize blk_m{ 1,3,2 };
	BlockSize blk_rhs{ 1,1 };
	
	s_blk_map(blk_m, blk_m, A, A_blk);
	s_blk_map(blk_m, blk_m, result_llt, L_blk);
	s_blk_llt(blk_m, A_blk, BlockStride{3,1,6,1}, L_blk, BlockStride{ 3,1,6,1 });
	if (!s_is_equal(36, llt, result_llt, error))std::cout << "\"s_blk_llt\" failed" << std::endl;

	s_vc(36, A, result_llt);
	s_blk_llt(blk_m, L_blk, BlockStride{ 3,1,6,1 }, L_blk, BlockStride{ 3,1,6,1 });
	if (!s_is_equal(36, llt, result_llt, error))std::cout << "\"s_blk_llt\" failed" << std::endl;

	s_blk_map(blk_m, blk_rhs, b, b_blk);
	s_blk_map(blk_m, blk_rhs, result_x, x_blk);
	s_blk_sov_lm(blk_m, blk_rhs, L_blk, BlockStride{ 3,1,6,1 }, b_blk, BlockStride{ 2,1,2,1 }, x_blk, BlockStride{ 2,1,2,1 });
	if (!s_is_equal(12, inv_l_dot_b, result_x, error))std::cout << "\"s_blk_sov_lm\" failed" << std::endl;
	
	s_vc(12, b, result_x);
	s_blk_sov_lm(blk_m, blk_rhs, L_blk, BlockStride{ 3,1,6,1 }, x_blk, BlockStride{ 2,1,2,1 }, x_blk, BlockStride{ 2,1,2,1 });
	if (!s_is_equal(12, inv_l_dot_b, result_x, error))std::cout << "\"s_blk_sov_lm\" failed" << std::endl;

	s_blk_sov_um(blk_m, blk_rhs, L_blk, BlockStride{ 3,1,6,1 }, b_blk, BlockStride{ 2,1,2,1 }, x_blk, BlockStride{ 2,1,2,1 });
	if (!s_is_equal(12, inv_u_dot_b, result_x, error))std::cout << "\"s_blk_sov_um\" failed" << std::endl;

	s_vc(12, b, result_x);
	s_blk_sov_um(blk_m, blk_rhs, L_blk, BlockStride{ 3,1,6,1 }, x_blk, BlockStride{ 2,1,2,1 }, x_blk, BlockStride{ 2,1,2,1 });
	if (!s_is_equal(12, inv_u_dot_b, result_x, error))std::cout << "\"s_blk_sov_um\" failed" << std::endl;

}
void test_block_householder()
{
	// test 6*5 mat	
	const aris::Size m{ 6 }, n{ 6 }, rhs{ 2 };
	const aris::Size a_t{ 9 }, q_t{ 8 }, r_t{ 6 }, u_t{ 7 }, tau_t{ 2 }, b_t{ 4 }, x_t{ 3 };
	double A[]{ 0.4018,0.4173,0.3377,0.2417,0.5752,0.0430,
		0.0760,0.0497,0.9001,0.4039,0.0598,0.1690,
		0.2399,0.9027,0.3692,0.0965,0.2348,0.6491,
		0.1233,0.9448,0.1112,0.1320,0.3532,0.7317,
		0.1839,0.4909,0.7803,0.9421,0.8212,0.6477,
		0.2400,0.4893,0.3897,0.9561,0.0154,0.4509 };
	double Q[]{
		-0.6207938622228, -0.154560758796689,0.479344322039396, -0.321468254294596, 0.500625274984451, 0.0835910815985244,
		-0.07429409790932, -0.17707859766604, -0.287176127497771, -0.79778986158619, -0.321450823922257, -0.37530538713139,
		-0.120089741851373, -0.771426698803364, -0.254652968468967, 0.386622567240651, 0.169145687493211, -0.384114429341121,
		-0.108126487111103, -0.273077416783337, -0.506838341291211, -0.139647719197317, 0.0441331940078665, 0.797121733949575,
		-0.499637333324524,   0.521984537055711, -0.580180031408702, 0.157727038950421, 0.239035801052366, -0.243454053933954,
		-0.57736038959889, -0.0511454590343965, 0.171513222014195, 0.257552294569938, -0.747226595652759, 0.0997074095924538 };
	double R[]{
		-1.31235189259588, -1.19204640068418, -0.984116392323211, -1.62724008099373, -1.10207955515584,
		0, -1.07261967566136, -0.681782306693105, -0.447503294312055, -0.80248312849391,
		0,0, -1.22940896476355, -0.79172515549949, -1.02847417900777,
		0,0,0, -0.664332641480675, -0.646519613301525,
		0,0,0,0,0.218449022247435,
		0,0,0,0,0 };
	double U[]{
		-0.575667742712756, - 1.23718660462685, - 0.943951918235489, - 0.99007388761123, - 0.851624789135743, - 0.874440397907058,
		0.0777519264104593,   0.913175949821214,   0.032721614441423,   0.0417771171744303,   0.159557266857079,   0.832622982803778,
		0.245430094024595, - 0.500586082775274, - 0.97031625360389, - 0.687654481098945, - 0.218181375942839, - 0.325762182814773,
		0.126142270084337, - 0.74194922437732,   0.368377141580173,   0.771433505997451,   0.0271772104508554,   0.200433857043914,
		0.188139200880046, - 0.181053735850886,   0.481220091509385, - 0.561472301309603, - 0.624382850137958, - 0.0487703636707999,
		0.245532399190924, - 0.0837301070313581,   0.0988415554285287, - 0.746722368949397, - 0.316506025763699, - 0.058064445582116 };
	double tau[]{
		-1.69797205955396,
		- 1.08644502819582,
		- 1.4523862600327,
		- 1.06789378117385,
		- 1.81789084930802,
		- 0.0552504598971324};
	const double b[]{
		0.5060,0.1493,
		0.6991,0.2575,
		0.8909,0.8407,
		0.9593,0.2543,
		0.5472,0.8143,
		0.1386,0.2435};
	const double x[]{
		0.209748905164346, 0.947708395923203,
		0.072279163615098, -0.200871645791878,
		0.169848963487236, 0.699653165641312,
		-0.524722596591983, -1.04635860123482,
		1.13918462877824,0.723696504731286,};
	const double A_ld[]{ 0.8147,0.9058, 0.127,0.9134,0.6324,0,0,0,0,
		0.0975,0.2785,0.5469,0.9575,0.9649,0,0,0,0,
		0.1576,0.9706,0.9572,0.4854,0.8003,0,0,0,0,
		0.1419,0.4218,0.9157,0.7922,0.9595,0,0,0,0,
		0.6557,0.0357,0.8491, 0.934,0.6787,0,0,0,0,
		0.7577,0.7431,0.3922,0.6555,0.1712,0,0,0,0 };
	const double Q_ld[]{
		-0.6207938622228, -0.154560758796689,0.479344322039396, -0.321468254294596, 0.500625274984451, 0.0835910815985244,0,0,
		-0.07429409790932, -0.17707859766604, -0.287176127497771, -0.79778986158619, -0.321450823922257, -0.37530538713139,0,0,
		-0.120089741851373, -0.771426698803364, -0.254652968468967, 0.386622567240651, 0.169145687493211, -0.384114429341121,0,0,
		-0.108126487111103, -0.273077416783337, -0.506838341291211, -0.139647719197317, 0.0441331940078665, 0.797121733949575,0,0,
		-0.499637333324524,   0.521984537055711, -0.580180031408702, 0.157727038950421, 0.239035801052366, -0.243454053933954,0,0,
		-0.57736038959889, -0.0511454590343965, 0.171513222014195, 0.257552294569938, -0.747226595652759, 0.0997074095924538,0,0 };
	const double R_ld[]{
		-1.31235189259588, -1.19204640068418, -0.984116392323211, -1.62724008099373, -1.10207955515584,0,
		0, -1.07261967566136, -0.681782306693105, -0.447503294312055, -0.80248312849391,0,
		0,0, -1.22940896476355, -0.79172515549949, -1.02847417900777,0,
		0,0,0, -0.664332641480675, -0.646519613301525,0,
		0,0,0,0,0.218449022247435,0,
		0,0,0,0,0,0 };
	const double U_ld[]{
		-1.31235189259588, -1.19204640068418, -0.984116392323211, -1.62724008099373,-1.10207955515584,0,0,
		0.0458380918394095, -1.07261967566136, -0.681782306693105, -0.447503294312055,-0.802483128493911,0,0,
		0.0740931617834968,0.64955454096634, -1.22940896476355, -0.79172515549949,-1.02847417900777,0,0,
		0.0667120536616637,0.224587809775278,0.43088167987985, -0.664332641480675,-0.646519613301525,0,0,
		0.30826704429847, -0.486866265436373,0.806399797389196,0.64673735967616,0.218449022247434,0,0,
		0.356220740376622, -0.00334385430562029,0.000250527139268941, -0.275874736646322,0.711610030647557,0,0 };
	const double tau_ld[]{
		-1.6207938622228,0,
		-1.16999382740955,0,
		-1.08936038603983,0,
		-1.33835118423397,0,
		-1.32767845364868,0,
		0,0 };
	const double b_ld[]{
		0.5060,0.1493,0,0,
		0.6991,0.2575,0,0,
		0.8909,0.8407,0,0,
		0.9593,0.2543,0,0,
		0.5472,0.8143,0,0,
		0.1386,0.2435,0,0};
	const double x_ld[]{
		0.209748905164346, 0.947708395923203,0,
		0.072279163615098, -0.200871645791878,0,
		0.169848963487236, 0.699653165641312,0,
		-0.524722596591983, -1.04635860123482,0,
		1.13918462877824,0.723696504731286,0,};
	
	double result1[100], result2[100];

	BlockData A_blk(3 * 3), U_blk(3 * 3), tau_blk(3 * 1);
	BlockSize blk_m{ 3,1,2 };

	s_blk_map(blk_m, blk_m, A, A_blk);
	s_blk_map(blk_m, blk_m, result1, U_blk);
	s_blk_map(blk_m, { 1 }, result2, tau_blk);
	s_blk_householder_ut(blk_m, A_blk, U_blk, tau_blk);

	//dsp(6, 6, result1);
	//if (!s_is_equal(36, llt, result_llt, error))std::cout << "\"s_blk_llt\" failed" << std::endl;


	//s_householder_ut(m, n, A, result1, result2);
	//dlmwrite("C:\\Users\\py033\\Desktop\\U.txt", result1, m, n);
	//dlmwrite("C:\\Users\\py033\\Desktop\\t.txt", result2, m, 1);
}


void test_block_matrix()
{
	std::cout << std::endl << "-----------------test block matrix--------------------" << std::endl;

	test_block_multiply();
	test_block_llt();
	test_block_householder();

	std::cout << "-----------------test block matrix finished-----------" << std::endl << std::endl;
}