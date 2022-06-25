#include "computeFunctions.h"

char *get_source_code(const char *file_name, size_t *len) {
	char *source_code;
	size_t length;
	FILE *file = fopen(file_name, "r");
	if (file == NULL) {
		printf("[%s:%d] OpenCL error %d/\n", __FILE__, __LINE__, file_name);
		exit(EXIT_FAILURE);
	}

	fseek(file, 0, SEEK_END);
	length = (size_t)ftell(file);
	rewind(file);

	source_code = (char *)malloc(length + 1);
	fread(source_code, length, 1, file);
	source_code[length] = '\0';

	fclose(file);
	*len = length;
	return source_code;
}

GPGPU::GPGPU(int flag)
{
	if (flag == CPU)
	{
		int platform = 0;
		cl_int nError;
		cl_int nProgramError = -1;
		while (nProgramError != CL_SUCCESS) {
			//��� ������ �÷��� ���� ��ȯ
			if (clGetPlatformIDs(0, NULL, &uiPlatformIDSize) != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 2 << std::endl;
			}
			//�÷��� ������ŭ id�� new ����
			pPlatformIDs = new cl_platform_id[uiPlatformIDSize];
			if (pPlatformIDs == 0) {
				std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
			}
			//�÷��� id ��� ��ȯ
			if (clGetPlatformIDs(uiPlatformIDSize, pPlatformIDs, NULL) != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 2 << std::endl;
			}
			//����̽� ����
			if (clGetDeviceIDs(pPlatformIDs[platform], CL_DEVICE_TYPE_CPU, 0, NULL, &uiDeviceIDSize) != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 2 << std::endl;
				if (platform < uiPlatformIDSize - 1) { platform++; continue; }
				else break;
			}
			//����̽� ������ŭ ����̽� �޸� �Ҵ�
			pDeviceIDs = new cl_device_id[uiDeviceIDSize];
			if (pDeviceIDs == 0)
			{
				std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
			}
			//����̽� ��ȯ
			if (clGetDeviceIDs(pPlatformIDs[platform], CL_DEVICE_TYPE_CPU, uiDeviceIDSize, pDeviceIDs, NULL) != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 2 << std::endl;
			}
			//���ؽ�Ʈ ����
			cl_context_properties Properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)pPlatformIDs[platform], 0, };
			pContext = clCreateContext(Properties, uiDeviceIDSize, pDeviceIDs, NULL, NULL, &nError);
			if (pContext == 0 || nError != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
			}
			//Ŀ��Ʈ ť ����, ù��° ����̽� ����
			pCommandQueue = clCreateCommandQueueWithProperties(pContext, pDeviceIDs[0], 0, &nError);
			if (pCommandQueue == 0 || nError != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
			}
			//���α׷� ����
			char *uiSourceCode;
			size_t uiSourceLength;
			uiSourceCode = get_source_code("computeFunctions.cl", &uiSourceLength);
			pProgram = clCreateProgramWithSource(pContext, 1, (const char **)&uiSourceCode, &uiSourceLength, &nError);
			if (pProgram == 0 || nError != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
			}
			//���α׷� ����
			nProgramError = clBuildProgram(pProgram, uiDeviceIDSize, pDeviceIDs, 0, 0, 0);
			if (nProgramError != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
			}
		}
	}
	else if (flag == GPU)
	{
		int platform = 0;
		cl_int nError;
		cl_int nProgramError = -1;
		while (nProgramError != CL_SUCCESS) {
			//��� ������ �÷��� ���� ��ȯ
			if (clGetPlatformIDs(0, NULL, &uiPlatformIDSize) != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 2 << std::endl;
			}
			//�÷��� ������ŭ id�� new ����
			pPlatformIDs = new cl_platform_id[uiPlatformIDSize];
			if (pPlatformIDs == 0) {
				std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
			}
			//�÷��� id ��� ��ȯ
			if (clGetPlatformIDs(uiPlatformIDSize, pPlatformIDs, NULL) != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 2 << std::endl;
			}
			//����̽� ����
			if (clGetDeviceIDs(pPlatformIDs[platform], CL_DEVICE_TYPE_GPU, 0, NULL, &uiDeviceIDSize) != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 2 << std::endl;
				if (platform < uiPlatformIDSize - 1) { platform++; continue; }
				else break;
			}
			//����̽� ������ŭ ����̽� �޸� �Ҵ�
			pDeviceIDs = new cl_device_id[uiDeviceIDSize];
			if (pDeviceIDs == 0)
			{
				std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
			}
			//����̽� ��ȯ
			if (clGetDeviceIDs(pPlatformIDs[platform], CL_DEVICE_TYPE_GPU, uiDeviceIDSize, pDeviceIDs, NULL) != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 2 << std::endl;
			}
			//���ؽ�Ʈ ����
			cl_context_properties Properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)pPlatformIDs[platform], 0, };
			pContext = clCreateContext(Properties, uiDeviceIDSize, pDeviceIDs, NULL, NULL, &nError);
			if (pContext == 0 || nError != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
			}
			//Ŀ��Ʈ ť ����, ù��° ����̽� ����
			pCommandQueue = clCreateCommandQueueWithProperties(pContext, pDeviceIDs[0], 0, &nError);
			if (pCommandQueue == 0 || nError != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
			}
			//���α׷� ����
			char *uiSourceCode;
			size_t uiSourceLength;
			uiSourceCode = get_source_code("computeFunctions.cl", &uiSourceLength);
			pProgram = clCreateProgramWithSource(pContext, 1, (const char **)&uiSourceCode, &uiSourceLength, &nError);
			if (pProgram == 0 || nError != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
			}
			//���α׷� ����
			nProgramError = clBuildProgram(pProgram, uiDeviceIDSize, pDeviceIDs, 0, 0, 0);
			if (nProgramError != CL_SUCCESS)
			{
				std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
			}
		}
	}
}

void GPGPU::destroy()
{
	//�÷��� ����
	if (pPlatformIDs != 0) delete[] pPlatformIDs;
	//����̽� ����
	if (pDeviceIDs != 0) delete[] pDeviceIDs;
	//Ŀ�� ����
	if (pKernel) clReleaseKernel(pKernel);
	//Ŀ�ǵ� ť ����
	if (pCommandQueue) clReleaseCommandQueue(pCommandQueue);
	//���ý�Ʈ ����
	if (pContext) clReleaseContext(pContext);
	//���α׷� ����
	if (pProgram) clReleaseProgram(pProgram);
}

void matrixMultiplication(GPGPU cgu, float *A, float *B, float *Y, int A_row, int A_col, int B_row, int B_col)
{
	if (A_row*B_col < 20000)
	{
		for (int i = 0; i < A_row; i++) {
			for (int j = 0; j < A_col; j++) {
				for (int k = 0; k < B_col; k++) {
					Y[i*B_col + k] += A[i*A_col + j] * B[j*B_col + k];
				}
			}
		}
	}
	else
	{
		cl_int nError;
		//Ŀ�� ����
		cgu.pKernel = clCreateKernel(cgu.pProgram, "matMul", &nError);
		if (cgu.pKernel == 0 || nError != CL_SUCCESS)
		{
			std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
		}
		//Matrix ������ ����
		int *size = (int*)malloc(sizeof(int) * 4);
		size[0] = A_row; size[1] = A_col; size[2] = B_row; size[3] = B_col;
		//Ŀ�� ����� ���� ����
		cl_mem pInputBufA = 0, pInputBufB = 0, pOutputBufY = 0, pSizeBuf = 0;
		pInputBufA = clCreateBuffer(cgu.pContext, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(int) * A_row * A_col, A, &nError);
		pInputBufB = clCreateBuffer(cgu.pContext, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(int) * B_row * B_col, B, &nError);
		pOutputBufY = clCreateBuffer(cgu.pContext, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, sizeof(int) * A_row * B_col, Y, &nError);
		pSizeBuf = clCreateBuffer(cgu.pContext, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(int) * 4, size, &nError);
		//work size ����
		size_t global_size[2] = { B_col,A_row };
		size_t local_size[2] = { 16,16 };
		global_size[0] = (global_size[0] + local_size[0] - 1) / local_size[0] * local_size[0];
		global_size[1] = (global_size[1] + local_size[1] - 1) / local_size[1] * local_size[1];
		//Ŀ�ο� �� ���� ����
		clSetKernelArg(cgu.pKernel, 0, sizeof(cl_mem), (void*)&pInputBufA);
		clSetKernelArg(cgu.pKernel, 1, sizeof(cl_mem), (void*)&pInputBufB);
		clSetKernelArg(cgu.pKernel, 2, sizeof(cl_mem), (void *)&pOutputBufY);
		clSetKernelArg(cgu.pKernel, 3, sizeof(cl_mem), (void*)&pSizeBuf);
		//Ŀ�� ����
		nError = clEnqueueNDRangeKernel(cgu.pCommandQueue, cgu.pKernel, 2, 0, global_size, local_size, 0, NULL, NULL);
		if (nError != CL_SUCCESS)
		{
			std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
		}
		//Ŀ�� ���� ���� �� ���� �б�
		nError = clEnqueueReadBuffer(cgu.pCommandQueue, pOutputBufY, CL_TRUE, 0, sizeof(int) * A_row * B_col, Y, 0, NULL, NULL);
		if (nError != CL_SUCCESS)
		{
			std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
		}
		//���� ����
		if (pInputBufA) clReleaseMemObject(pInputBufA);
		if (pInputBufB) clReleaseMemObject(pInputBufB);
		if (pOutputBufY) clReleaseMemObject(pOutputBufY);
		if (pSizeBuf) clReleaseMemObject(pSizeBuf);
	}
}

void convolution(GPGPU cgu, float *X, float *F, float *Y, int X_height, int X_width, int F_height, int F_width, int Y_height, int Y_width, int stride)
{
	if (Y_height*Y_width < 20000)
	{
		//����
	}
	else
	{
		//����
	}
}

void convolution(GPGPU cgu, float *X, float *F, float *Y, int X_depth, int X_height, int X_width, int F_height, int F_width, int Y_depth, int Y_height, int Y_width, int stride, int num)
{
	if (Y_depth*Y_height*Y_width*num < 20000)
	{
		for (int i = 0; i < num * Y_depth; i++) {
			for (int j = 0; j < Y_height * Y_width; j++) {
				for (int k = (i / Y_depth) * X_depth; k < (i / Y_depth + 1) * X_depth; k++) {
					for (int m = 0; m < F_height; m++) {
						for (int n = 0; n < F_width; n++) {
							Y[i*Y_height*Y_width + j] += X[k*X_height*X_width + (stride*(j / Y_width) + m)*X_width + (stride*(j%Y_width) + n)] * F[k*Y_depth*F_height*F_width + (i%Y_depth)*F_height*F_width + m*F_width + n];
						}
					}
				}
			}
		}
	}
	else
	{
		cl_int nError;
		//Ŀ�� ����
		cgu.pKernel = clCreateKernel(cgu.pProgram, "convolution", &nError);
		if (cgu.pKernel == 0 || nError != CL_SUCCESS)
		{
			std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
		}
		//Matrix ������ ����
		int *size = (int*)malloc(sizeof(int) * 10);
		size[0] = X_depth; size[1] = X_height; size[2] = X_width; size[3] = Y_depth; size[4] = Y_height; size[5] = Y_width, size[6] = F_height; size[7] = F_width; size[8] = stride; size[9] = num;
		//Ŀ�� ����� ���� ����
		cl_mem pInputBufX = 0, pInputBufF = 0, pOutputBufY = 0, pSizeBuf = 0;
		pInputBufX = clCreateBuffer(cgu.pContext, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(int) * num * X_depth * X_height * X_width, X, &nError);
		pInputBufF = clCreateBuffer(cgu.pContext, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(int) * num * X_depth * Y_depth * F_height * F_width, F, &nError);
		pOutputBufY = clCreateBuffer(cgu.pContext, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, sizeof(int) * num * Y_depth * Y_height * Y_width, Y, &nError);
		pSizeBuf = clCreateBuffer(cgu.pContext, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(int) * 10, size, &nError);
		//work size ����
		size_t global_size[2] = { Y_height * Y_width ,  Y_depth * num };
		size_t local_size[2] = { 16, 16 };
		global_size[0] = (global_size[0] + local_size[0] - 1) / local_size[0] * local_size[0];
		global_size[1] = (global_size[1] + local_size[1] - 1) / local_size[1] * local_size[1];
		//Ŀ�ο� �� ���� ����
		clSetKernelArg(cgu.pKernel, 0, sizeof(cl_mem), (void*)&pInputBufX);
		clSetKernelArg(cgu.pKernel, 1, sizeof(cl_mem), (void*)&pInputBufF);
		clSetKernelArg(cgu.pKernel, 2, sizeof(cl_mem), (void *)&pOutputBufY);
		clSetKernelArg(cgu.pKernel, 3, sizeof(cl_mem), (void*)&pSizeBuf);
		//Ŀ�� ����
		clEnqueueNDRangeKernel(cgu.pCommandQueue, cgu.pKernel, 2, 0, global_size, local_size, 0, NULL, NULL);
		if (nError != CL_SUCCESS)
		{
			std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
		}
		//Ŀ�� ���� ���� �� ���� �б�
		clEnqueueReadBuffer(cgu.pCommandQueue, pOutputBufY, CL_TRUE, 0, sizeof(int) * num * Y_depth * Y_height * Y_width, Y, 0, NULL, NULL);
		if (nError != CL_SUCCESS)
		{
			std::cout << "Error - Line " << __LINE__ - 3 << std::endl;
		}
		//���� ����
		if (pInputBufX) clReleaseMemObject(pInputBufX);
		if (pInputBufF) clReleaseMemObject(pInputBufF);
		if (pOutputBufY) clReleaseMemObject(pOutputBufY);
		if (pSizeBuf) clReleaseMemObject(pSizeBuf);
	}	
}

