#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include"functions.h"

using namespace cv;
using namespace std;

int main() {
	DEVICES devices = getDevice();
	DEVICE dev = devices[showDevice(devices)];
	ParallelCompute pc(dev);

	vector<vector<vector<double>>> bias1;
	resizeVec(bias1,96, 1, 1);
	setRandom(bias1,0.001);
	vector<vector<vector<vector<double>>>> filter1;
	resizeVec(filter1,96, 3, 11, 11);
	setRandom(filter1,0.3);
	vector<vector<vector<double>>> bias2;
	resizeVec(bias2,256, 1, 1);
	setRandom(bias2,0.001);
	vector<vector<vector<vector<double>>>> filter2;
	resizeVec(filter2,256, 96, 5, 5);
	setRandom(filter2,0.1);
	vector<vector<vector<double>>> bias3;
	resizeVec(bias3,384, 1, 1);
	setRandom(bias3,0.001);
	vector<vector<vector<vector<double>>>> filter3;
	resizeVec(filter3,384, 256, 3, 3);
	setRandom(filter3,0.05);
	vector<vector<vector<double>>> bias4;
	resizeVec(bias4,384, 1, 1);
	setRandom(bias4,0.001);
	vector<vector<vector<vector<double>>>> filter4;
	resizeVec(filter4,384, 384, 3, 3);
	setRandom(filter4,0.01);
	vector<vector<vector<double>>> bias5;
	resizeVec(bias5,256, 1, 1);
	setRandom(bias5,0.001);
	vector<vector<vector<vector<double>>>> filter5;
	resizeVec(filter5,256, 384, 3, 3);
	setRandom(filter5,0.02);
	vector<vector<double>> bias6;
	resizeVec(bias6,1, 4096);
	setRandom(bias6,0.001);
	vector<vector<double>> weight6;
	resizeVec(weight6,9216, 4096);
	setRandom(weight6,0.001);
	vector<vector<double>> bias7;
	resizeVec(bias7,1, 4096);
	setRandom(bias7,0.001);
	vector<vector<double>> weight7;
	resizeVec(weight7,4096, 4096);
	setRandom(weight7,0.003);
	vector<vector<double>> bias8;
	resizeVec(bias8,1, 1000);
	setRandom(bias8,0.001);
	vector<vector<double>> weight8;
	resizeVec(weight8,4096, 1000);
	setRandom(weight8,0.005);

	vector<vector<double>> opt_weight8;
	resizeVec(opt_weight8, 4096, 1000);
	vector<vector<double>> opt_weight7;
	resizeVec(opt_weight7, 4096, 4096);
	vector<vector<double>> opt_weight6;
	resizeVec(opt_weight6, 9216, 4096);
	vector<vector<double>> opt_bias8;
	resizeVec(opt_bias8, 1, 1000);
	vector<vector<double>> opt_bias7;
	resizeVec(opt_bias7, 1, 4096);
	vector<vector<double>> opt_bias6;
	resizeVec(opt_bias6, 1, 4096);
	vector<vector<vector<vector<double>>>> opt_filter5;
	resizeVec(opt_filter5, 256, 384, 3, 3);
	vector<vector<vector<vector<double>>>> opt_filter4;
	resizeVec(opt_filter4, 384, 384, 3, 3);
	vector<vector<vector<vector<double>>>> opt_filter3;
	resizeVec(opt_filter3, 384, 256, 3, 3);
	vector<vector<vector<vector<double>>>> opt_filter2;
	resizeVec(opt_filter2, 256, 96, 5, 5);
	vector<vector<vector<vector<double>>>> opt_filter1;
	resizeVec(opt_filter1, 96, 3, 11, 11);
	vector<vector<vector<double>>> opt_bias5;
	resizeVec(opt_bias5, 256, 1, 1);
	vector<vector<vector<double>>> opt_bias4;
	resizeVec(opt_bias4, 384, 1, 1);
	vector<vector<vector<double>>> opt_bias3;
	resizeVec(opt_bias3, 384, 1, 1);
	vector<vector<vector<double>>> opt_bias2;
	resizeVec(opt_bias2, 256, 1, 1);
	vector<vector<vector<double>>> opt_bias1;
	resizeVec(opt_bias1, 96, 1, 1);

	vector<vector<double>> mom_weight8;
	resizeVec(mom_weight8, 4096, 1000);
	vector<vector<double>> mom_weight7;
	resizeVec(mom_weight7, 4096, 4096);
	vector<vector<double>> mom_weight6;
	resizeVec(mom_weight6, 9216, 4096);
	vector<vector<double>> mom_bias8;
	resizeVec(mom_bias8, 1, 1000);
	vector<vector<double>> mom_bias7;
	resizeVec(mom_bias7, 1, 4096);
	vector<vector<double>> mom_bias6;
	resizeVec(mom_bias6, 1, 4096);
	vector<vector<vector<vector<double>>>> mom_filter5;
	resizeVec(mom_filter5, 256, 384, 3, 3);
	vector<vector<vector<vector<double>>>> mom_filter4;
	resizeVec(mom_filter4, 384, 384, 3, 3);
	vector<vector<vector<vector<double>>>> mom_filter3;
	resizeVec(mom_filter3, 384, 256, 3, 3);
	vector<vector<vector<vector<double>>>> mom_filter2;
	resizeVec(mom_filter2, 256, 96, 5, 5);
	vector<vector<vector<vector<double>>>> mom_filter1;
	resizeVec(mom_filter1, 96, 3, 11, 11);
	vector<vector<vector<double>>> mom_bias5;
	resizeVec(mom_bias5, 256, 1, 1);
	vector<vector<vector<double>>> mom_bias4;
	resizeVec(mom_bias4, 384, 1, 1);
	vector<vector<vector<double>>> mom_bias3;
	resizeVec(mom_bias3, 384, 1, 1);
	vector<vector<vector<double>>> mom_bias2;
	resizeVec(mom_bias2, 256, 1, 1);
	vector<vector<vector<double>>> mom_bias1;
	resizeVec(mom_bias1, 96, 1, 1);

	string path = "C:\\Users\\kk\\Pictures\\CNN_AlexNet\\train\\*.jpg";
	vector<String> imagePath;
	imagePath = getImage(path);
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::shuffle(imagePath.begin(), imagePath.end(), e);

	int N = imagePath.size();
	for (int ep = 0; ep < 1000; ep++) {
		for (int dataNum = 0; dataNum < N; dataNum++) {
			vector<vector<double>> target = setTarget(imagePath[dataNum]);
			vector<vector<vector<double>>> input = setImage(imagePath[dataNum]);
			
			//feedforward
			vector<vector<vector<double>>> conv1 = convolution(pc, input, bias1, filter1,4);
			vector<vector<vector<double>>> activated1 = reluF(conv1);
			vector<vector<vector<double>>> positionx1;
			vector<vector<vector<double>>> positiony1;
			resizeVec(positionx1, activated1.size(), ((activated1[0].size() - 3) / 2) + 1, ((activated1[0][0].size() - 3) / 2) + 1);
			resizeVec(positiony1, activated1.size(), ((activated1[0].size() - 3) / 2) + 1, ((activated1[0][0].size() - 3) / 2) + 1);
			vector<vector<vector<double>>> pooled1 = maxPooling(activated1, positionx1, positiony1, 3, 2);
			vector<vector<vector<double>>> padded1 = padding(pooled1,2);
			vector<vector<vector<double>>> conv2 = convolution(pc, padded1, bias2, filter2, 1);
			vector<vector<vector<double>>> activated2 = reluF(conv2);
			vector<vector<vector<double>>> positionx2;
			vector<vector<vector<double>>> positiony2;
			resizeVec(positionx2, activated2.size(), ((activated2[0].size() - 3) / 2) + 1, ((activated2[0][0].size() - 3) / 2) + 1);
			resizeVec(positiony2, activated2.size(), ((activated2[0].size() - 3) / 2) + 1, ((activated2[0][0].size() - 3) / 2) + 1);
			vector<vector<vector<double>>> pooled2 = maxPooling(activated2, positionx2, positiony2, 3, 2);
			vector<vector<vector<double>>> padded2 = padding(pooled2, 1);
			vector<vector<vector<double>>> conv3 = convolution(pc, padded2, bias3, filter3, 1);
			vector<vector<vector<double>>> activated3 = reluF(conv3);
			vector<vector<vector<double>>> padded3 = padding(activated3, 1);
			vector<vector<vector<double>>> conv4 = convolution(pc, padded3, bias4, filter4,1);
			vector<vector<vector<double>>> activated4 = reluF(conv4);
			vector<vector<vector<double>>> padded4 = padding(activated4,1);
			vector<vector<vector<double>>> conv5 = convolution(pc, padded4, bias5, filter5, 1);
			vector<vector<vector<double>>> activated5 = reluF(conv5);
			vector<vector<vector<double>>> positionx5;
			vector<vector<vector<double>>> positiony5;
			resizeVec(positionx5, activated5.size(), ((activated5[0].size() - 3) / 2) + 1, ((activated5[0][0].size() - 3) / 2) + 1);
			resizeVec(positiony5, activated5.size(), ((activated5[0].size() - 3) / 2) + 1, ((activated5[0][0].size() - 3) / 2) + 1);
			vector<vector<vector<double>>> pooled5 = maxPooling(activated5, positionx5, positiony5, 3, 2);
			vector<vector<double>> flattened = flatten(pooled5);
			vector<vector<double>> fullconnected6;
			resizeVec(fullconnected6,1, 4096);
			multiplication(pc, flattened, fullconnected6, bias6, weight6);
			vector<vector<double>> activatedFull6 = reluF(fullconnected6);
			vector<vector<double>> fullconnected7;
			resizeVec(fullconnected7,1, 4096);
			multiplication(pc, activatedFull6, fullconnected7, bias7, weight7);
			vector<vector<double>> activatedFull7 = reluF(fullconnected7);
			vector<vector<double>> fullconnected8;
			resizeVec(fullconnected8,1, 1000);
			multiplication(pc, activatedFull7, fullconnected8, bias8, weight8);
			vector<vector<double>> Y = softmax(fullconnected8);
			vector<vector<double>> Loss = loss(Y, target);

			//backpropagation
			double momentum = 0.99;
			vector<vector<double>> error8 = calError(Loss, fullconnected8);
			vector<vector<double>> gradientWeight8 = calWeightDiff(bias8, error8, activatedFull7);
			vector<vector<double>> deltaBias8;
			resizeVec(deltaBias8, 1, 1000);
			vector<vector<double>> deltaWeight8;
			resizeVec(deltaWeight8, 4096, 1000);
			GDMoment(deltaWeight8, deltaBias8, opt_weight8, opt_bias8, gradientWeight8, error8, momentum, ep);
			updateWeight(weight8, deltaWeight8);
			updateBias2(bias8, deltaBias8);
			vector<vector<double>> errorIn7 = calError_in(pc, error8, weight8);
			vector<vector<double>> error7 = calError(errorIn7, fullconnected7);
			vector<vector<double>> gradientWeight7 = calWeightDiff(bias7, error7, activatedFull6);
			vector<vector<double>> deltaBias7;
			resizeVec(deltaBias7, 1, 4096);
			vector<vector<double>> deltaWeight7;
			resizeVec(deltaWeight7, 4096, 4096);
			GDMoment(deltaWeight7, deltaBias7, opt_weight7, opt_bias7, gradientWeight7, error7, momentum, ep);
			updateWeight(weight7, deltaWeight7);
			updateBias2(bias7, deltaBias7);
			vector<vector<double>> errorIn6 = calError_in(pc, error7, weight7);
			vector<vector<double>> error6 = calError(errorIn6, fullconnected6);
			vector<vector<double>> gradientWeight6 = calWeightDiff(bias6, error6, flattened);
			vector<vector<double>> deltaBias6;
			resizeVec(deltaBias6, 1, 4096);
			vector<vector<double>> deltaWeight6;
			resizeVec(deltaWeight6, 9216, 4096);
			GDMoment(deltaWeight6, deltaBias6, opt_weight6, opt_bias6, gradientWeight6, error6, momentum, ep);
			updateWeight(weight6, deltaWeight6);
			updateBias2(bias6, deltaBias6);
			vector<vector<double>> errorIn5 = calError_in(pc, error6, weight6);
			vector<vector<vector<double>>> dflattend = dflatten(errorIn5, 6);
			vector<vector<vector<double>>> pooledError5 = poolError(dflattend, positionx5, positiony5, 2, 3);
			vector<vector<vector<double>>> error5 = calError(pooledError5, conv5);
			vector<vector<vector<vector<double>>>> gradientFilter5 = calFilterDiff(filter5, bias5, error5, padded4, 1);
			vector<vector<vector<double>>> deltaBias5;
			resizeVec(deltaBias5, 256, 1, 1);
			vector<vector<vector<vector<double>>>> deltaFilter5;
			resizeVec(deltaFilter5, 256, 384, 3, 3);
			GDMoment(deltaFilter5, deltaBias5, opt_filter5, opt_bias5, gradientFilter5, error5, momentum, ep);
			updateFilter(filter5, deltaFilter5);
			updateBias(bias5, deltaBias5);
			vector<vector<vector<double>>> paddedError5 = padding(error5, 1);
			vector<vector<vector<double>>> errorIn4 = calError_in(pc, paddedError5, filter5, 1);
			vector<vector<vector<double>>> error4 = calError(errorIn4, conv4);
			vector<vector<vector<vector<double>>>> gradientFilter4 = calFilterDiff(filter4, bias4, error4, padded3, 1);
			vector<vector<vector<double>>> deltaBias4;
			resizeVec(deltaBias4, 384, 1, 1);
			vector<vector<vector<vector<double>>>> deltaFilter4;
			resizeVec(deltaFilter4, 384, 384, 3, 3);
			GDMoment(deltaFilter4, deltaBias4, opt_filter4, opt_bias4, gradientFilter4, error4, momentum, ep);
			updateFilter(filter4, deltaFilter4);
			updateBias(bias4, deltaBias4);
			vector<vector<vector<double>>> paddedError4 = padding(error4, 1);
			vector<vector<vector<double>>> errorIn3 = calError_in(pc, paddedError4, filter4, 1);
			vector<vector<vector<double>>> error3 = calError(errorIn3, conv3);
			vector<vector<vector<vector<double>>>> gradientFilter3 = calFilterDiff(filter3, bias3, error3, padded2, 1);
			vector<vector<vector<double>>> deltaBias3;
			resizeVec(deltaBias3, 384, 1, 1);
			vector<vector<vector<vector<double>>>> deltaFilter3;
			resizeVec(deltaFilter3, 384, 256, 3, 3);
			GDMoment(deltaFilter3, deltaBias3, opt_filter3, opt_bias3, gradientFilter3, error3, momentum, ep);
			updateFilter(filter3, deltaFilter3);
			updateBias(bias3, deltaBias3);
			vector<vector<vector<double>>> paddedError3 = padding(error3, 1);
			vector<vector<vector<double>>> errorIn2 = calError_in(pc, paddedError3, filter3, 1);
			vector<vector<vector<double>>> pooledError2 = poolError(errorIn2, positionx2, positiony2, 2, 3);
			vector<vector<vector<double>>> error2 = calError(pooledError2, conv2);
			vector<vector<vector<vector<double>>>> gradientFilter2 = calFilterDiff(filter2, bias2, error2, padded1, 1);
			vector<vector<vector<double>>> deltaBias2;
			resizeVec(deltaBias2, 256, 1, 1);
			vector<vector<vector<vector<double>>>> deltaFilter2;
			resizeVec(deltaFilter2, 256, 96, 5, 5);
			GDMoment(deltaFilter2, deltaBias2, opt_filter2, opt_bias2, gradientFilter2, error2, momentum, ep);
			updateFilter(filter2, deltaFilter2);
			updateBias(bias2, deltaBias2);
			vector<vector<vector<double>>> paddedError2 = padding(error2, 2);
			vector<vector<vector<double>>> errorIn1 = calError_in(pc, paddedError2, filter2, 1);
			vector<vector<vector<double>>> pooledError1 = poolError(errorIn1, positionx1, positiony1, 2, 3);
			vector<vector<vector<double>>> error1 = calError(pooledError1, conv1);
			vector<vector<vector<vector<double>>>> gradientFilter1 = calFilterDiff(filter1, bias1, error1, input, 4);
			vector<vector<vector<double>>> deltaBias1;
			resizeVec(deltaBias1, 96, 1, 1);
			vector<vector<vector<vector<double>>>> deltaFilter1;
			resizeVec(deltaFilter1, 96, 3, 11, 11);
			GDMoment(deltaFilter1, deltaBias1, opt_filter1, opt_bias1, gradientFilter1, error1, momentum, ep);
			updateFilter(filter1, deltaFilter1);
			updateBias(bias1, deltaBias1);

			cout << ep << " Train Result: " << Y[0][0]<< "(" << target[0][0] << ") ";
			cout << Y[0][1] << "(" << target[0][1] << ") ";
			cout << Y[0][2] << "(" << target[0][2] << ") " << endl;
			
			for (int i = 0; i < 3; i++) {
				if (target[0][i] == 1)
					if (target[0][i] - Y[0][i] < 0.001) break;
			}
		}
	}
	system("pause");
	return 0;
}
