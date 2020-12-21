xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 264;
 -878.08317;216.90720;-842.61958;,
 -878.08317;-184.61160;-842.61958;,
 -878.08317;-184.61160;-13820.44373;,
 -878.08317;216.90720;-13820.44373;,
 807.15598;-184.61160;-842.61958;,
 807.15598;216.90720;-842.61958;,
 807.15598;216.90720;-13820.44373;,
 807.15598;-184.61160;-13820.44373;,
 -754.18561;-184.61160;-14509.98413;,
 -754.18561;216.90720;-14509.98413;,
 864.81361;216.90720;-14042.13135;,
 864.81361;-184.61160;-14042.13135;,
 -456.91919;-184.61160;-15130.95886;,
 -456.91919;216.90720;-15130.95886;,
 967.61158;216.90720;-14230.53040;,
 967.61158;-184.61160;-14230.53040;,
 8.34840;-184.61160;-15636.16846;,
 8.34840;216.90720;-15636.16846;,
 1135.68839;216.90720;-14383.51172;,
 1135.68839;-184.61160;-14383.51172;,
 567.92519;-184.61160;-16014.59692;,
 567.92519;216.90720;-16014.59692;,
 1288.26357;216.90720;-14491.05798;,
 1288.26357;-184.61160;-14491.05798;,
 6072.27484;-184.61160;-18617.10425;,
 6072.27484;216.90720;-18617.10425;,
 6792.62036;216.90720;-17093.55981;,
 6792.62036;-184.61160;-17093.55981;,
 6309.02142;-184.61160;-18796.31543;,
 6309.02142;216.90720;-18796.31543;,
 7328.24615;216.90720;-17454.14978;,
 7328.24615;-184.61160;-17454.14978;,
 6489.33838;-184.61160;-18999.36255;,
 6489.33838;216.90720;-18999.36255;,
 7896.47058;216.90720;-18071.89893;,
 7896.47058;-184.61160;-18071.89893;,
 6603.94446;-184.61160;-19210.16602;,
 6603.94446;216.90720;-19210.16602;,
 8179.53827;216.90720;-18612.17358;,
 8179.53827;-184.61160;-18612.17358;,
 6655.99329;-184.61160;-19458.00000;,
 6655.99329;216.90720;-19458.00000;,
 8332.95959;216.90720;-19291.07593;,
 8332.95959;-184.61160;-19291.07593;,
 7871.76727;-184.61160;-31728.17065;,
 7871.76727;216.90720;-31728.17065;,
 9548.72314;216.90720;-31561.27515;,
 9548.72314;-184.61160;-31561.27515;,
 8111.43018;-184.61160;-32634.26367;,
 8111.43018;216.90720;-32634.26367;,
 9662.74146;216.90720;-31975.88379;,
 9662.74146;-184.61160;-31975.88379;,
 8471.28955;-184.61160;-33299.39575;,
 8471.28955;216.90720;-33299.39575;,
 9838.51611;216.90720;-32314.14624;,
 9838.51611;-184.61160;-32314.14624;,
 8969.52612;-184.61160;-33821.39795;,
 8969.52612;216.90720;-33821.39795;,
 10036.12720;216.90720;-32516.64404;,
 10036.12720;-184.61160;-32516.64404;,
 9662.74915;-184.61160;-34239.21021;,
 9662.74915;216.90720;-34239.21021;,
 10307.28955;216.90720;-32682.11353;,
 10307.28955;-184.61160;-32682.11353;,
 10472.60852;-184.61160;-34439.24487;,
 10472.60852;216.90720;-34439.24487;,
 10616.68103;216.90720;-32760.19336;,
 10616.68103;-184.61160;-32760.19336;,
 11064.74744;-184.61160;-34457.08228;,
 11064.74744;216.90720;-34457.08228;,
 10927.97974;216.90720;-32777.47485;,
 10927.97974;-184.61160;-32777.47485;,
 40176.94922;-184.61160;-32086.70728;,
 40176.94922;216.90720;-32086.70728;,
 40040.19141;216.90720;-30407.04053;,
 40040.19141;-184.61160;-30407.04053;,
 41229.06152;-184.61160;-31779.75146;,
 41229.06152;216.90720;-31779.75146;,
 40722.71045;216.90720;-30172.37476;,
 40722.71045;-184.61160;-30172.37476;,
 42147.31201;-184.61160;-31349.46533;,
 42147.31201;216.90720;-31349.46533;,
 41277.12891;216.90720;-29906.26172;,
 41277.12891;-184.61160;-29906.26172;,
 42972.93457;-184.61160;-30648.38818;,
 42972.93457;216.90720;-30648.38818;,
 41717.24121;216.90720;-29524.47583;,
 41717.24121;-184.61160;-29524.47583;,
 48266.49463;-184.61160;-24734.26538;,
 48266.49463;216.90720;-24734.26538;,
 47010.71777;216.90720;-23610.30908;,
 47010.71777;-184.61160;-23610.30908;,
 48643.98047;-184.61160;-24416.98462;,
 48643.98047;216.90720;-24416.98462;,
 47778.18311;216.90720;-22971.22119;,
 47778.18311;-184.61160;-22971.22119;,
 49210.43115;-184.61160;-24072.33691;,
 49210.43115;216.90720;-24072.33691;,
 49247.41553;216.90720;-22251.78369;,
 49247.41553;-184.61160;-22251.78369;,
 51019.80469;-184.61160;-24699.01025;,
 51019.80469;216.90720;-24699.01025;,
 51079.51758;216.90720;-21437.42432;,
 51079.51758;-184.61160;-21437.42432;,
 53528.42725;-184.61160;-24008.09326;,
 53528.42725;216.90720;-24008.09326;,
 52263.29004;216.90720;-20899.01514;,
 52263.29004;-184.61160;-20899.01514;,
 56606.35693;-184.61160;-22918.82300;,
 56606.35693;216.90720;-22918.82300;,
 53069.40527;216.90720;-20335.44287;,
 53069.40527;-184.61160;-20335.44287;,
 58420.38428;-184.61160;-21250.76660;,
 58420.38428;216.90720;-21250.76660;,
 53985.09814;216.90720;-19729.30737;,
 53985.09814;-184.61160;-19729.30737;,
 60144.80713;-184.61160;-17855.65393;,
 60144.80713;216.90720;-17855.65393;,
 55302.44238;216.90720;-17728.07080;,
 55302.44238;-184.61160;-17728.07080;,
 59414.67334;-184.61160;-14247.27026;,
 59414.67334;216.90720;-14247.27026;,
 54911.19727;216.90720;-15641.44958;,
 54911.19727;-184.61160;-15641.44958;,
 56629.52051;-184.61160;-11373.37537;,
 56629.52051;216.90720;-11373.37537;,
 53574.21826;216.90720;-13883.76343;,
 53574.21826;-184.61160;-13883.76343;,
 53853.24463;-184.61160;-9661.97571;,
 53853.24463;216.90720;-9661.97571;,
 51728.98096;216.90720;-12172.34180;,
 51728.98096;-184.61160;-12172.34180;,
 50208.37646;-184.61160;-8909.39905;,
 50208.37646;216.90720;-8909.39905;,
 47795.41846;216.90720;-10929.19702;,
 47795.41846;-184.61160;-10929.19702;,
 49298.06250;-184.61160;-8402.09381;,
 49298.06250;216.90720;-8402.09381;,
 46056.55957;216.90720;-9510.33911;,
 46056.55957;-184.61160;-9510.33911;,
 49162.23193;-184.61160;-7742.12750;,
 49162.23193;216.90720;-7742.12750;,
 45696.60352;216.90720;-7181.90277;,
 45696.60352;-184.61160;-7181.90277;,
 53257.03857;-184.61160;-2592.57596;,
 53257.03857;216.90720;-2592.57596;,
 47149.64209;216.90720;-2032.35480;,
 47149.64209;-184.61160;-2032.35480;,
 54394.63770;-184.61160;1359.35280;,
 54394.63770;216.90720;1359.35280;,
 48252.55078;216.90720;1123.09202;,
 48252.55078;-184.61160;1123.09202;,
 54121.67578;-184.61160;5677.34766;,
 54121.67578;216.90720;5677.34766;,
 47979.59766;216.90720;5441.09052;,
 47979.59766;-184.61160;5441.09052;,
 52743.02783;-184.61160;9612.75916;,
 52743.02783;216.90720;9612.75916;,
 47090.61035;216.90720;7723.34253;,
 47090.61035;-184.61160;7723.34253;,
 47640.81445;-184.61160;14144.13721;,
 47640.81445;216.90720;14144.13721;,
 44311.42969;216.90720;11638.17773;,
 44311.42969;-184.61160;11638.17773;,
 46711.99512;-184.61160;15518.87622;,
 46711.99512;216.90720;15518.87622;,
 42784.42236;216.90720;14126.39319;,
 42784.42236;-184.61160;14126.39319;,
 46229.26025;-184.61160;17070.64893;,
 46229.26025;216.90720;17070.64893;,
 42526.10742;216.90720;17123.46460;,
 42526.10742;-184.61160;17123.46460;,
 45659.96631;-184.61160;18479.69385;,
 45659.96631;216.90720;18479.69385;,
 43095.43652;216.90720;19754.64624;,
 43095.43652;-184.61160;19754.64624;,
 47269.08105;-184.61160;21025.64136;,
 47269.08105;216.90720;21025.64136;,
 45112.83838;216.90720;22910.48657;,
 45112.83838;-184.61160;22910.48657;,
 50097.90234;-184.61160;22728.62109;,
 50097.90234;216.90720;22728.62109;,
 46483.50586;216.90720;24613.42676;,
 46483.50586;-184.61160;24613.42676;,
 51639.78516;-184.61160;26104.34619;,
 51639.78516;216.90720;26104.34619;,
 47291.98975;216.90720;26220.87378;,
 47291.98975;-184.61160;26220.87378;,
 51186.94189;-184.61160;29112.51270;,
 51186.94189;216.90720;29112.51270;,
 47266.00488;216.90720;27889.04224;,
 47266.00488;-184.61160;27889.04224;,
 48767.80518;-184.61160;31865.49976;,
 48767.80518;216.90720;31865.49976;,
 45517.00781;216.90720;29679.38306;,
 45517.00781;-184.61160;29679.38306;,
 44996.12842;-184.61160;34264.46118;,
 44996.12842;216.90720;34264.46118;,
 43172.52979;216.90720;30747.68262;,
 43172.52979;-184.61160;30747.68262;,
 39649.32861;-184.61160;33567.04907;,
 39649.32861;216.90720;33567.04907;,
 40742.20898;216.90720;30176.35840;,
 40742.20898;-184.61160;30176.35840;,
 36361.25024;-184.61160;31659.44678;,
 36361.25024;216.90720;31659.44678;,
 38941.91455;216.90720;29138.71289;,
 38941.91455;-184.61160;29138.71289;,
 34893.65479;-184.61160;28093.21216;,
 34893.65479;216.90720;28093.21216;,
 36699.76538;216.90720;26973.16479;,
 36699.76538;-184.61160;26973.16479;,
 33537.32007;-184.61160;25156.19092;,
 33537.32007;216.90720;25156.19092;,
 35343.41748;216.90720;24036.16992;,
 35343.41748;-184.61160;24036.16992;,
 33097.97900;-184.61160;24321.78369;,
 33097.97900;216.90720;24321.78369;,
 34401.66943;216.90720;22643.46387;,
 34401.66943;-184.61160;22643.46387;,
 32162.40308;-184.61160;23818.13306;,
 32162.40308;216.90720;23818.13306;,
 32944.72412;216.90720;21842.15845;,
 32944.72412;-184.61160;21842.15845;,
 31141.81714;-184.61160;23796.18677;,
 31141.81714;216.90720;23796.18677;,
 31057.93872;216.90720;21672.65479;,
 31057.93872;-184.61160;21672.65479;,
 30194.50781;-184.61160;24242.24268;,
 30194.50781;216.90720;24242.24268;,
 29239.70142;216.90720;22343.61621;,
 29239.70142;-184.61160;22343.61621;,
 19908.62183;-184.61160;29160.70532;,
 19908.62183;216.90720;29160.70532;,
 19174.17920;216.90720;27659.59277;,
 19174.17920;-184.61160;27659.59277;,
 18420.73572;-184.61160;29526.86206;,
 18420.73572;216.90720;29526.86206;,
 18525.88696;216.90720;27859.02759;,
 18525.88696;-184.61160;27859.02759;,
 17229.36951;-184.61160;29408.29102;,
 17229.36951;216.90720;29408.29102;,
 17859.45959;216.90720;27860.49316;,
 17859.45959;-184.61160;27860.49316;,
 10730.64221;-184.61160;26750.49390;,
 10730.64221;216.90720;26750.49390;,
 11606.54810;216.90720;25327.27881;,
 11606.54810;-184.61160;25327.27881;,
 6339.32666;-184.61160;23172.53467;,
 6339.32666;216.90720;23172.53467;,
 7370.17932;216.90720;21857.20972;,
 7370.17932;-184.61160;21857.20972;,
 2681.95331;-184.61160;18797.73486;,
 2681.95331;216.90720;18797.73486;,
 4077.10080;216.90720;17877.77271;,
 4077.10080;-184.61160;17877.77271;,
 -586.21680;-184.61160;13506.20947;,
 -586.21680;216.90720;13506.20947;,
 1084.39199;216.90720;13463.66492;,
 1084.39199;-184.61160;13463.66492;,
 -877.59002;-184.61160;838.37157;,
 -877.59002;216.90720;838.37157;,
 793.55518;216.90720;843.79319;,
 793.55518;-184.61160;843.79319;;
 
 132;
 4;3,2,1,0;,
 4;7,6,5,4;,
 4;9,8,2,3;,
 4;11,10,6,7;,
 4;13,12,8,9;,
 4;15,14,10,11;,
 4;17,16,12,13;,
 4;19,18,14,15;,
 4;21,20,16,17;,
 4;23,22,18,19;,
 4;25,24,20,21;,
 4;27,26,22,23;,
 4;29,28,24,25;,
 4;31,30,26,27;,
 4;33,32,28,29;,
 4;35,34,30,31;,
 4;37,36,32,33;,
 4;39,38,34,35;,
 4;41,40,36,37;,
 4;43,42,38,39;,
 4;45,44,40,41;,
 4;47,46,42,43;,
 4;49,48,44,45;,
 4;51,50,46,47;,
 4;53,52,48,49;,
 4;55,54,50,51;,
 4;57,56,52,53;,
 4;59,58,54,55;,
 4;61,60,56,57;,
 4;63,62,58,59;,
 4;65,64,60,61;,
 4;67,66,62,63;,
 4;69,68,64,65;,
 4;71,70,66,67;,
 4;73,72,68,69;,
 4;75,74,70,71;,
 4;77,76,72,73;,
 4;79,78,74,75;,
 4;81,80,76,77;,
 4;83,82,78,79;,
 4;85,84,80,81;,
 4;87,86,82,83;,
 4;89,88,84,85;,
 4;91,90,86,87;,
 4;93,92,88,89;,
 4;95,94,90,91;,
 4;97,96,92,93;,
 4;99,98,94,95;,
 4;101,100,96,97;,
 4;103,102,98,99;,
 4;105,104,100,101;,
 4;107,106,102,103;,
 4;109,108,104,105;,
 4;111,110,106,107;,
 4;113,112,108,109;,
 4;115,114,110,111;,
 4;117,116,112,113;,
 4;119,118,114,115;,
 4;121,120,116,117;,
 4;123,122,118,119;,
 4;125,124,120,121;,
 4;127,126,122,123;,
 4;129,128,124,125;,
 4;131,130,126,127;,
 4;133,132,128,129;,
 4;135,134,130,131;,
 4;137,136,132,133;,
 4;139,138,134,135;,
 4;141,140,136,137;,
 4;143,142,138,139;,
 4;145,144,140,141;,
 4;147,146,142,143;,
 4;149,148,144,145;,
 4;151,150,146,147;,
 4;153,152,148,149;,
 4;155,154,150,151;,
 4;157,156,152,153;,
 4;159,158,154,155;,
 4;161,160,156,157;,
 4;163,162,158,159;,
 4;165,164,160,161;,
 4;167,166,162,163;,
 4;169,168,164,165;,
 4;171,170,166,167;,
 4;173,172,168,169;,
 4;175,174,170,171;,
 4;177,176,172,173;,
 4;179,178,174,175;,
 4;181,180,176,177;,
 4;183,182,178,179;,
 4;185,184,180,181;,
 4;187,186,182,183;,
 4;189,188,184,185;,
 4;191,190,186,187;,
 4;193,192,188,189;,
 4;195,194,190,191;,
 4;197,196,192,193;,
 4;199,198,194,195;,
 4;201,200,196,197;,
 4;203,202,198,199;,
 4;205,204,200,201;,
 4;207,206,202,203;,
 4;209,208,204,205;,
 4;211,210,206,207;,
 4;213,212,208,209;,
 4;215,214,210,211;,
 4;217,216,212,213;,
 4;219,218,214,215;,
 4;221,220,216,217;,
 4;223,222,218,219;,
 4;225,224,220,221;,
 4;227,226,222,223;,
 4;229,228,224,225;,
 4;231,230,226,227;,
 4;233,232,228,229;,
 4;235,234,230,231;,
 4;237,236,232,233;,
 4;239,238,234,235;,
 4;241,240,236,237;,
 4;243,242,238,239;,
 4;245,244,240,241;,
 4;247,246,242,243;,
 4;249,248,244,245;,
 4;251,250,246,247;,
 4;253,252,248,249;,
 4;255,254,250,251;,
 4;257,256,252,253;,
 4;259,258,254,255;,
 4;261,260,256,257;,
 4;263,262,258,259;,
 4;262,263,4,5;,
 4;260,261,0,1;;
 
 MeshMaterialList {
  28;
  132;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.520800;0.775200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.260400;0.387600;0.400000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\4bc9133c7fd6f47e59e9f30ec9a3e398--crossword-texture.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Texture1png.png";
   }
  }
  Material {
   0.800000;0.344800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.431000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;0.882000;0.835000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.300000;0.264600;0.250500;;
   TextureFilename {
    "46ef3c42b25b9ffcb37a5f7c1109aa2b.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "eb83d30f8a6fc6868ca5da857d0e26ce.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.500000;0.500000;0.500000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\コンテスト\\thang-tang-arkship-techtile_(3).jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;1.000000;1.000000;;
   TextureFilename {
    "アイテムテクスチャ.png";
   }
  }
  Material {
   0.000000;0.787200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.492000;0.500000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\4bc9133c7fd6f47e59e9f30ec9a3e398--crossword-texture.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "アイテムテクスチャ.png";
   }
  }
  Material {
   0.800000;0.222400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.278000;0.000000;;
  }
  Material {
   0.800000;0.232000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.290000;0.000000;;
   TextureFilename {
    "Binario.svg.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.540000;0.596000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.337500;0.372500;0.500000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\4bc9133c7fd6f47e59e9f30ec9a3e398--crossword-texture.jpg";
   }
  }
  Material {
   0.800000;0.000000;0.028000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.000000;0.035000;;
   TextureFilename {
    "アイテムテクスチャ.png";
   }
  }
  Material {
   0.800000;0.222400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.278000;0.000000;;
  }
  Material {
   0.800000;0.222400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.278000;0.000000;;
  }
  Material {
   0.800000;0.222400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.278000;0.000000;;
  }
  Material {
   0.800000;0.222400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.278000;0.000000;;
  }
  Material {
   0.800000;0.222400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.278000;0.000000;;
  }
  Material {
   0.800000;0.222400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.278000;0.000000;;
  }
  Material {
   0.800000;0.222400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.278000;0.000000;;
  }
  Material {
   0.800000;0.222400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.278000;0.000000;;
  }
  Material {
   0.800000;0.222400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.278000;0.000000;;
  }
  Material {
   0.000000;0.800000;0.780800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;1.000000;0.976000;;
  }
  Material {
   0.353000;0.353000;0.353000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.353000;0.353000;0.353000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\コンテスト\\depositphotos_91961950-stock-illustration-vector-cracked-ground-and-lava.jpg";
   }
  }
  Material {
   0.800000;0.232000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.290000;0.000000;;
   TextureFilename {
    "Binario.svg.png";
   }
  }
 }
 MeshNormals {
  132;
  0.999992;0.000000;0.004032;,
  -1.000000;0.000000;0.000147;,
  0.991918;0.000000;0.126881;,
  -0.996052;0.000000;-0.088775;,
  0.929785;0.000000;0.368104;,
  -0.951682;0.000000;-0.307084;,
  0.786339;0.000000;0.617795;,
  -0.827942;0.000000;-0.560813;,
  0.625835;0.000000;0.779955;,
  -0.652273;0.000000;-0.757984;,
  0.503655;0.000000;0.863905;,
  -0.495267;0.000000;-0.868740;,
  0.494352;0.000000;0.869262;,
  -0.518251;0.000000;-0.855229;,
  0.651702;0.000000;0.758475;,
  -0.678916;0.000000;-0.734216;,
  0.817847;0.000000;0.575436;,
  -0.818460;0.000000;-0.574563;,
  0.938536;0.000000;0.345180;,
  -0.938517;0.000000;-0.345232;,
  0.987147;0.000000;0.159817;,
  -0.988336;0.000000;-0.152289;,
  0.983199;0.000000;0.182535;,
  -0.984081;0.000000;-0.177721;,
  0.930946;0.000000;0.365158;,
  -0.929679;0.000000;-0.368372;,
  0.810254;0.000000;0.586079;,
  -0.808604;0.000000;-0.588353;,
  0.623144;0.000000;0.782107;,
  -0.625326;0.000000;-0.780364;,
  0.387164;0.000000;0.922011;,
  -0.382297;0.000000;-0.924039;,
  0.150754;0.000000;0.988571;,
  -0.135713;0.000000;-0.990748;,
  -0.012893;0.000000;0.999917;,
  0.025561;0.000000;-0.999673;,
  -0.204745;0.000000;0.978815;,
  0.181545;0.000000;-0.983383;,
  -0.379573;0.000000;0.925162;,
  0.353248;0.000000;-0.935530;,
  -0.548885;0.000000;0.835898;,
  0.540561;0.000000;-0.841305;,
  -0.701598;0.000000;0.712573;,
  0.697824;0.000000;-0.716269;,
  -0.694375;0.000000;0.719613;,
  0.696017;0.000000;-0.718026;,
  -0.543721;0.000000;0.839266;,
  0.583294;0.000000;-0.812261;,
  -0.423049;0.000000;0.906107;,
  0.106388;0.000000;-0.994325;,
  -0.410099;0.000000;0.912041;,
  -0.032326;0.000000;-0.999477;,
  -0.495576;0.000000;0.868565;,
  0.299767;0.000000;-0.954013;,
  -0.562520;0.000000;0.826784;,
  0.515698;0.000000;-0.856770;,
  -0.708012;0.000000;0.706201;,
  0.796914;0.000000;-0.604092;,
  -0.980382;0.000000;0.197108;,
  0.990880;0.000000;-0.134744;,
  -0.913978;0.000000;-0.405764;,
  0.884823;0.000000;0.465928;,
  -0.740728;0.000000;-0.671805;,
  0.626261;0.000000;0.779613;,
  -0.502897;0.000000;-0.864346;,
  0.369078;0.000000;0.929399;,
  -0.475254;0.000000;-0.879849;,
  0.348544;0.000000;0.937292;,
  -0.867876;0.000000;-0.496780;,
  0.806447;0.000000;0.591307;,
  -0.998151;0.000000;0.060783;,
  0.972652;0.000000;-0.232266;,
  -0.953656;0.000000;0.300899;,
  0.888818;0.000000;-0.458261;,
  -0.990690;0.000000;0.136137;,
  0.994112;0.000000;-0.108362;,
  -0.976486;0.000000;-0.215579;,
  0.980058;0.000000;0.198713;,
  -0.880257;0.000000;-0.474498;,
  0.830511;0.000000;0.557002;,
  -0.834326;0.000000;-0.551272;,
  0.752212;0.000000;0.658921;,
  -0.949799;0.000000;-0.312860;,
  0.901363;0.000000;0.433065;,
  -0.997981;0.000000;0.063515;,
  0.941822;0.000000;0.336112;,
  -0.924551;0.000000;0.381058;,
  0.995968;0.000000;-0.089711;,
  -0.811986;0.000000;0.583677;,
  0.699378;0.000000;-0.714752;,
  -0.840894;0.000000;0.541199;,
  0.746055;0.000000;-0.665885;,
  -0.974745;0.000000;0.223320;,
  0.990283;0.000000;-0.139069;,
  -0.923132;0.000000;-0.384482;,
  0.906795;0.000000;0.421572;,
  -0.574765;0.000000;-0.818318;,
  0.650453;0.000000;0.759547;,
  -0.098175;0.000000;-0.995169;,
  0.216668;0.000000;0.976245;,
  0.368020;0.000000;-0.929818;,
  -0.321868;0.000000;0.946784;,
  0.601553;0.000000;-0.798833;,
  -0.753288;0.000000;0.657690;,
  0.815210;0.000000;-0.579166;,
  -0.916516;0.000000;0.399999;,
  0.870979;0.000000;-0.491320;,
  -0.896657;0.000000;0.442727;,
  0.673940;0.000000;-0.738786;,
  -0.710350;0.000000;0.703848;,
  0.291903;0.000000;-0.956448;,
  -0.254829;0.000000;0.966986;,
  -0.131577;0.000000;-0.991306;,
  0.207760;0.000000;0.978180;,
  -0.407495;0.000000;-0.913207;,
  0.428700;0.000000;0.903447;,
  -0.382197;0.000000;-0.924081;,
  0.336942;0.000000;0.941526;,
  -0.149756;0.000000;-0.988723;,
  0.070989;0.000000;0.997477;,
  0.190193;0.000000;-0.981747;,
  -0.241302;0.000000;0.970450;,
  0.510359;0.000000;-0.859961;,
  -0.510660;0.000000;0.859782;,
  0.705333;0.000000;-0.708877;,
  -0.702628;0.000000;0.711557;,
  0.799971;0.000000;-0.600039;,
  -0.811082;0.000000;0.584932;,
  0.952510;0.000000;-0.304507;,
  -0.958775;0.000000;0.284167;,
  0.999972;0.000000;-0.007488;,
  -0.999932;0.000000;0.011645;;
  132;
  4;3,3,1,1;,
  4;2,2,0,0;,
  4;5,5,3,3;,
  4;4,4,2,2;,
  4;7,7,5,5;,
  4;6,6,4,4;,
  4;9,9,7,7;,
  4;8,8,6,6;,
  4;11,11,9,9;,
  4;10,10,8,8;,
  4;13,13,11,11;,
  4;12,12,10,10;,
  4;15,15,13,13;,
  4;14,14,12,12;,
  4;17,17,15,15;,
  4;16,16,14,14;,
  4;19,19,17,17;,
  4;18,18,16,16;,
  4;21,21,19,19;,
  4;20,20,18,18;,
  4;23,23,21,21;,
  4;22,22,20,20;,
  4;25,25,23,23;,
  4;24,24,22,22;,
  4;27,27,25,25;,
  4;26,26,24,24;,
  4;29,29,27,27;,
  4;28,28,26,26;,
  4;31,31,29,29;,
  4;30,30,28,28;,
  4;33,33,31,31;,
  4;32,32,30,30;,
  4;35,35,33,33;,
  4;34,34,32,32;,
  4;37,37,35,35;,
  4;36,36,34,34;,
  4;39,39,37,37;,
  4;38,38,36,36;,
  4;41,41,39,39;,
  4;40,40,38,38;,
  4;43,43,41,41;,
  4;42,42,40,40;,
  4;45,45,43,43;,
  4;44,44,42,42;,
  4;47,47,45,45;,
  4;46,46,44,44;,
  4;49,49,47,47;,
  4;48,48,46,46;,
  4;51,51,49,49;,
  4;50,50,48,48;,
  4;53,53,51,51;,
  4;52,52,50,50;,
  4;55,55,53,53;,
  4;54,54,52,52;,
  4;57,57,55,55;,
  4;56,56,54,54;,
  4;59,59,57,57;,
  4;58,58,56,56;,
  4;61,61,59,59;,
  4;60,60,58,58;,
  4;63,63,61,61;,
  4;62,62,60,60;,
  4;65,65,63,63;,
  4;64,64,62,62;,
  4;67,67,65,65;,
  4;66,66,64,64;,
  4;69,69,67,67;,
  4;68,68,66,66;,
  4;71,71,69,69;,
  4;70,70,68,68;,
  4;73,73,71,71;,
  4;72,72,70,70;,
  4;75,75,73,73;,
  4;74,74,72,72;,
  4;77,77,75,75;,
  4;76,76,74,74;,
  4;79,79,77,77;,
  4;78,78,76,76;,
  4;81,81,79,79;,
  4;80,80,78,78;,
  4;83,83,81,81;,
  4;82,82,80,80;,
  4;85,85,83,83;,
  4;84,84,82,82;,
  4;87,87,85,85;,
  4;86,86,84,84;,
  4;89,89,87,87;,
  4;88,88,86,86;,
  4;91,91,89,89;,
  4;90,90,88,88;,
  4;93,93,91,91;,
  4;92,92,90,90;,
  4;95,95,93,93;,
  4;94,94,92,92;,
  4;97,97,95,95;,
  4;96,96,94,94;,
  4;99,99,97,97;,
  4;98,98,96,96;,
  4;101,101,99,99;,
  4;100,100,98,98;,
  4;103,103,101,101;,
  4;102,102,100,100;,
  4;105,105,103,103;,
  4;104,104,102,102;,
  4;107,107,105,105;,
  4;106,106,104,104;,
  4;109,109,107,107;,
  4;108,108,106,106;,
  4;111,111,109,109;,
  4;110,110,108,108;,
  4;113,113,111,111;,
  4;112,112,110,110;,
  4;115,115,113,113;,
  4;114,114,112,112;,
  4;117,117,115,115;,
  4;116,116,114,114;,
  4;119,119,117,117;,
  4;118,118,116,116;,
  4;121,121,119,119;,
  4;120,120,118,118;,
  4;123,123,121,121;,
  4;122,122,120,120;,
  4;125,125,123,123;,
  4;124,124,122,122;,
  4;127,127,125,125;,
  4;126,126,124,124;,
  4;129,129,127,127;,
  4;128,128,126,126;,
  4;131,131,129,129;,
  4;130,130,128,128;,
  4;130,130,0,0;,
  4;131,131,1,1;;
 }
 MeshTextureCoords {
  264;
  0.625000;0.500000;,
  0.625000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.750000;,
  0.375000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;;
 }
}
