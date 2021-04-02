#include "OpenCLWrapper.h"

#include <string.h>

char * openKernel(char* fileName)
{
	char* kernelDir = "kernels/";

	char* fileToOpen = (char*)malloc(1 + strlen(kernelDir) + strlen(fileName));
	
	strcpy(fileToOpen, kernelDir);
	strcat(fileToOpen, fileName);

	if(!fileToOpen)
	{
		fprintf(stderr, "Error generating kernel char.");
		exit(1);
	}
	
	return fileToOpen;
}

struct DeviceInfo initDeviceInfo()
{
	struct DeviceInfo out;

	out.plat_id = NULL;
	out.dev_id = NULL;
	out.num_dev = -1;
	out.num_plat = -1;

	return out;
}


struct SourceInfo getSourceInfo(FILE* f)
{
	struct SourceInfo info;

	info.str = (char*)(malloc(MAX_SOURCE_SIZE));
	info.size = fread(info.str, 1, MAX_SOURCE_SIZE, f);


	return info;
}
