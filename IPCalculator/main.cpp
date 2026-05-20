#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<CommCtrl.h>
#include<iostream>
#include"resource.h" 


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, (DLGPROC)DlgProc, NULL);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		//InitCommonControls();
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		std::cout << "Init" << std::endl;
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_IP_ADDRESS:
		{
			DWORD dwIPaddress = 0;
			DWORD dwIPmask = 0;
			HWND hIPadress = GetDlgItem(hwnd, IDC_IP_ADDRESS);
			HWND hIPmask = GetDlgItem(hwnd, IDC_IP_MASK);
			if (HIWORD(wParam) == EN_CHANGE)
			{
				SendMessage(hIPadress, IPM_GETADDRESS, 0, (LPARAM)&dwIPaddress);
				std::cout << FIRST_IPADDRESS(dwIPaddress) << std::endl;
				if (FIRST_IPADDRESS(dwIPaddress) < 128)dwIPmask = 0xFF000000;
				else if (FIRST_IPADDRESS(dwIPaddress) < 192)dwIPmask = 0xFFFF0000;
				else if (FIRST_IPADDRESS(dwIPaddress) < 224)dwIPmask = 0xFFFFFF00;
				std::cout << dwIPmask << std::endl;
				SendMessage(hIPmask, IPM_SETADDRESS, 0, dwIPmask);
			}
		}
			break;
		case IDOK:
			break;
		case IDCANCEL:EndDialog(hwnd, 0);
		}
	}
	break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}
