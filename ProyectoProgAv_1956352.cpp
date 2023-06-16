// ProyectoProgAv_1956352.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ProyectoProgAv_1956352.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>
#include "string"
#include <commdlg.h>
#include <commctrl.h>
#include <math.h>
#include <chrono>

#define MAX_LOADSTRING 100


struct PERSONA {
    int ID = 0;
    char nombre[255] = { '\0' };
    char password[255] = { '\0' };
    char empresa[255] = { '\0' };
    TCHAR foto[255] = { '\0' };
};
struct NODO_PERSONA {
    NODO_PERSONA* siguiente = nullptr;
    PERSONA persona;
    NODO_PERSONA* anterior = nullptr;
};
struct LISTA_PERSONA
{
    NODO_PERSONA* inicio = nullptr;
    NODO_PERSONA* fin = nullptr;
    int cantidad;
}listaPersona;

struct ARTICULO {
    int ID = 0;
    float precio = 0;
    char nombre[255] = { '\0' };
    char marca[255] = { '\0' };
    char descripion[255] = { '\0' };
    int cantidad = 0;
    TCHAR foto1[255] = { '\0' };
    TCHAR foto2[255] = { '\0' };
    int IdPersona = 0;
};
struct NODO_ARTICULO {
    NODO_ARTICULO* siguiente = nullptr;
    ARTICULO articulo;
    NODO_ARTICULO* anterior = nullptr;
};
struct LISTA_ARTICULO
{
    NODO_ARTICULO* inicio = nullptr;
    NODO_ARTICULO* fin = nullptr;
    int cantidad;
}listaArticulo;

struct ENVIO
{
    int ID = 0;
    int IdArticulo[255] = { '\0' };
    int Cantidad = 0;
    float Total = 0;
    char Calle[255] = { '\0' };
    char Colonia[255] = { '\0' };
    char Ciudad[255] = { '\0' };
    char Estado[255] = { '\0' };
    char FechaDeEntrega[255] = { '\0' };
    int IdPersona = 0;
};
struct NODO_ENVIO {
    NODO_ENVIO* siguiente = nullptr;
    ENVIO envio;
    NODO_ENVIO* anterior = nullptr;
};
struct LISTA_ENVIO
{
    NODO_ENVIO* inicio = nullptr;
    NODO_ENVIO* fin = nullptr;
    int cantidad;
}listaEnvio, listaEnvioPorFecha;


void agregar(PERSONA);
void agregar(ARTICULO);
void agregar(ENVIO, ARTICULO);
void agregar(ENVIO);

NODO_PERSONA* buscarP(int);
NODO_ARTICULO* buscarA(int);
NODO_ENVIO* buscarE(int);

void borrarP(int);
void borrarA(int);
void borrarE(int);


void mostrarP(HWND, int);
void mostrarA(HWND, int, int);
void mostrarE(HWND, int, int);

void mostrarObjetoP(HWND, PERSONA, int);
void mostrarObjetoA(HWND, ARTICULO, int);
void mostrarObjetoE(HWND, ENVIO, int);

void modificarP(PERSONA, int);
void modificarA(ARTICULO, int);
void modificarE(ENVIO, int);

void guardarLista();
void cargarLista();
bool contieneSoloLetras(char*); 
void convertirAMayusculas(char*);
char* TextDlg(HWND);
bool comprobarNombreArticulo(char*); 
char* obtenerFechaActual(int);
char* redondearhora(int);

bool buscarPersona(int); 
bool buscarArticulo(int);
bool buscarEnvio(int);

//bool ordenarPorFecha(int);

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    iniciarSesion(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    MostrarUsuarios(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AgregarArticulo(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Envios(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    // 
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROYECTOPROGAV1956352, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROYECTOPROGAV1956352));

    MSG msg = {};

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = {0};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_NOCLOSE | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROYECTOPROGAV1956352));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROYECTOPROGAV1956352);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~(WS_MINIMIZEBOX | WS_THICKFRAME),
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   cargarLista();

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_INICIARSESION:
                DialogBox(hInst, MAKEINTRESOURCE(DLG_INICIARSESION), hWnd, iniciarSesion);
                break;
            case IDM_MOSTRARUSUARIOS:
                DialogBox(hInst, MAKEINTRESOURCE(DLG_MOSTRARUSUARIOS), hWnd, MostrarUsuarios);
                break;
            case IDM_AGREGARARTICULO:
                DialogBox(hInst, MAKEINTRESOURCE(DLG_CARGARUSUARIO), hWnd, AgregarArticulo);
                break;
            case IDM_ENVIOS:
            {
                DialogBox(hInst, MAKEINTRESOURCE(DLG_TABLAENVIOS), hWnd, Envios);
            }
            break;
            case IDM_EXIT:
                if (MessageBoxA(hWnd, "¿Está seguro de que desea cerrar el programa? ", "Confirmar cierre", MB_OKCANCEL) == IDOK)
                {
                    guardarLista();
                    DestroyWindow(hWnd);
                }
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


INT_PTR CALLBACK iniciarSesion(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (wParam)
        {
        case BTN_IMAGEN:
        {
            HWND hImagenEstatica = GetDlgItem(hDlg, STATIC_IMAGE);
            HWND hImagen = GetDlgItem(hDlg, IMG_USUARIO);

            OPENFILENAME ofn;
            TCHAR szFile[MAX_PATH] = { 0 };

            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hDlg;
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = _T("Bitmap Files (*.bmp)\0*.bmp\0All Files (*.*)\0*.*\0");
            ofn.nFilterIndex = 1;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn))
            {
                HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, szFile, IMAGE_BITMAP, 95, 95, LR_LOADFROMFILE);
                SetWindowText(hImagenEstatica, szFile);
                SendMessage(hImagen, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);

            }
            return (INT_PTR)TRUE;
        }
        break;
        case BTN_REGISTRO:
        {
            PERSONA persona;
            HWND hNombre = GetDlgItem(hDlg, IDC_NOMBRE);
            HWND hEmpresa = GetDlgItem(hDlg, IDC_EMPRESA);
            HWND hPassword = GetDlgItem(hDlg, IDC_PASSWORD);
            HWND hImagen = GetDlgItem(hDlg, STATIC_IMAGE);
            TCHAR bufferI[MAX_PATH]; // imagen
            int SizeN = GetWindowTextLengthA(hNombre) + 1;
            int SizeE = GetWindowTextLengthA(hEmpresa) + 1;
            int SizeP = GetWindowTextLengthA(hPassword) + 1;
            char* bufferN = new char[SizeN]; // nombre
            char* bufferE = new char[SizeE]; // empresa
            char* bufferP = new char[SizeP]; // password
            GetWindowTextA(hNombre, bufferN, SizeN);
            GetWindowTextA(hEmpresa, bufferE, SizeE);
            GetWindowTextA(hPassword, bufferP, SizeP);

            if (GetWindowTextLengthA(hNombre) + 1 > 1 && GetWindowTextLengthA(hEmpresa) + 1 > 1 && GetWindowTextLengthA(hPassword) + 1 > 1)
            {
                if (contieneSoloLetras(bufferN))
                {
                    strncpy_s(persona.nombre, bufferN, sizeof(persona.nombre) - 1);
                    persona.nombre[sizeof(persona.nombre) - 1] = '\0';
                    convertirAMayusculas(bufferE);
                    strncpy_s(persona.empresa, bufferE, sizeof(persona.empresa) - 1);
                    persona.empresa[sizeof(persona.empresa) - 1] = '\0';
                    strncpy_s(persona.password, bufferP, sizeof(persona.password) - 1);
                    persona.password[sizeof(persona.password) - 1] = '\0';

                    GetWindowText(hImagen, bufferI, MAX_PATH);

                    lstrcpy(persona.foto, bufferI);

                    agregar(persona);
                    MessageBoxA(hDlg, "Usuario agregado con exito", "CHECK", MB_OK);
                }
                else
                {
                    MessageBoxA(hDlg, "Su nombre no puede contener caracteres o numeros, solo letras", "ERROR", MB_OK);
                }
            }
            else
            {
                MessageBoxA(hDlg, "inserte su nombre, su empresa o su password correctamente", "ERROR", MB_OK);
            }
            delete[] bufferN;
            delete[] bufferE;
            delete[] bufferP;

            return (INT_PTR)TRUE;
        }
        break;
        default:
            break;
            return (INT_PTR)FALSE;
        }
        break;
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        break;
    case WM_DESTROY:
        return (INT_PTR)FALSE;
        break;
    default:
        return (INT_PTR)FALSE;
    }
}
INT_PTR CALLBACK MostrarUsuarios(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        HWND hListBox = GetDlgItem(hDlg, LB_USUARIOS);
        mostrarP(hListBox, 1);
        return (INT_PTR)TRUE;
    }
    break;
    case WM_COMMAND:
        switch (wParam)
        {
        case BTN_BORRARUSUARIO2:
        {
            try
            {
                PERSONA persona;
                HWND hID = GetDlgItem(hDlg, IDC_STATIC_ID);
                HWND hPassword = GetDlgItem(hDlg, IDC_PASSWORDBORRAR);
                int size = GetWindowTextLengthA(hID) + 1;
                char* buffer = new char[size];
                int sizePassword = GetWindowTextLengthA(hPassword) + 1;
                char* bufferPassword = new char[sizePassword];
                GetWindowTextA(hID, buffer, size);
                
                if (std::stoi(buffer) > 0)
                {
                    borrarP(std::stoi(buffer));
                    SetWindowTextA(hID, "0");
                }
                else
                {
                    MessageBoxA(hDlg, "No haz iniciado sesion", "ERROR", MB_OK);
                }
                delete[] buffer;
            }
            catch (const std::exception& e)
            {
                MessageBoxA(NULL, e.what(), "ERROR", MB_OK);
            }
            
        }
        break;
        case BTN_MODIFICARUSUARIO:
        {
            try
            {
                PERSONA persona;

                HWND hId = GetDlgItem(hDlg, IDC_STATIC_ID);
                HWND hNombre = GetDlgItem(hDlg, IDC_NOMBRE);
                HWND hEmpresa = GetDlgItem(hDlg, IDC_EMPRESA);
                HWND hPassword = GetDlgItem(hDlg, IDC_PASSWORDBORRAR);
                HWND hEstetica = GetDlgItem(hDlg, STATIC_IMAGE2);
                int sizeId = GetWindowTextLengthA(hId) + 1;
                char* bufferId = new char[sizeId];
                GetWindowTextA(hId, bufferId, sizeId);
                int sizeNombre = GetWindowTextLengthA(hNombre) + 1;
                char* bufferNombre = new char[sizeNombre];
                GetWindowTextA(hNombre, bufferNombre, sizeNombre);
                int sizeEmpresa = GetWindowTextLengthA(hEmpresa) + 1;
                char* bufferEmpresa = new char[sizeEmpresa];
                GetWindowTextA(hEmpresa, bufferEmpresa, sizeEmpresa);
                int sizePassword = GetWindowTextLengthA(hPassword) + 1;
                char* bufferPassword = new char[sizePassword];
                GetWindowTextA(hPassword, bufferPassword, sizePassword);
                int sizeI = GetWindowTextLengthA(hEstetica) + 1;
                TCHAR* bufferI = new TCHAR[sizeI];
                GetWindowTextW(hEstetica, bufferI, sizeI);

                if (GetWindowTextLengthA(hNombre) + 1 > 1 && GetWindowTextLengthA(hEmpresa) + 1 > 1 && GetWindowTextLengthA(hPassword) + 1 > 1)
                {
                    if (contieneSoloLetras(bufferNombre))
                    {
                        strncpy_s(persona.nombre, bufferNombre, sizeof(persona.nombre) - 1);
                        persona.nombre[sizeof(persona.nombre) - 1] = '\0';
                        convertirAMayusculas(bufferEmpresa);
                        strncpy_s(persona.empresa, bufferEmpresa, sizeof(persona.empresa) - 1);
                        persona.empresa[sizeof(persona.empresa) - 1] = '\0';
                        strncpy_s(persona.password, bufferPassword, sizeof(persona.password) - 1);
                        persona.password[sizeof(persona.password) - 1] = '\0';

                        int length = GetWindowText(hEstetica, bufferI, MAX_PATH);

                        lstrcpy(persona.foto, bufferI);
                        if (std::stoi(bufferId) > 0)
                        {
                            modificarP(persona, std::stoi(bufferId));
                            HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, persona.foto, IMAGE_BITMAP, 95, 95, LR_LOADFROMFILE);
                            SendMessage(GetDlgItem(hDlg, IMG_USUARIO3), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
                            MessageBoxA(hDlg, "Usuario agregado con exito", "CHECK", MB_OK);

                        }
                        else
                        {
                            MessageBoxA(hDlg, "No haz iniciado sesion", "ERROR", MB_OK);
                        }
                    }
                    else
                    {
                        MessageBoxA(hDlg, "Su nombre no puede contener caracteres o numeros, solo letras", "ERROR", MB_OK);
                    }
                }
                else
                {
                    MessageBoxA(hDlg, "inserte su nombre, su empresa o su password correctamente", "ERROR", MB_OK);
                }

                delete[] bufferId;
                delete[] bufferNombre;
                delete[] bufferEmpresa;
                delete[] bufferPassword;
                delete[] bufferI;
            }
            catch (const std::exception& e)
            {
                MessageBoxA(NULL, e.what(), "ERROR", MB_OK);
            }
            return (INT_PTR)TRUE;
        }
        break;
        case IDC_MOSTRAR:
        {
            PERSONA persona;

            HWND hImagen = GetDlgItem(hDlg, IMG_USUARIO3);
            HWND hID = GetDlgItem(hDlg, IDC_STATIC_ID);
            HWND hNombre = GetDlgItem(hDlg, IDC_STATIC_NOMBRE);
            HWND hEmpresa = GetDlgItem(hDlg, IDC_STATIC_EMPRESA);

            HWND hBoxID = GetDlgItem(hDlg, IDC_ID);
            HWND hPassword = GetDlgItem(hDlg, IDC_PASSWORDBORRAR);
            int sizeId = GetWindowTextLengthA(hBoxID) + 1;
            char* bufferId = new char[sizeId];
            GetWindowTextA(hBoxID, bufferId, sizeId);
            int sizePassword = GetWindowTextLengthA(hPassword) + 1;
            char* bufferPassword = new char[sizePassword];
            GetWindowTextA(hPassword, bufferPassword, sizePassword);

            try
            {
                if (buscarPersona(std::stoi(bufferId)))
                {
                    persona = buscarP(std::stoi(bufferId))->persona;

                    if (strcmp(bufferPassword, persona.password) == 0)
                    {
                        SetWindowTextA(hID, bufferId);
                        SetWindowTextA(hNombre, persona.nombre);
                        SetWindowTextA(hEmpresa, persona.empresa);
                        HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, persona.foto, IMAGE_BITMAP, 95, 95, LR_LOADFROMFILE);
                        SendMessage(hImagen, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
                    }
                    else
                    {
                        MessageBoxA(hDlg, "contrasena incorrecta", "ERROR", MB_OK);
                    }
                }
                else
                {
                    MessageBoxA(hDlg, "El usuario no existe", "ERROR", MB_OK);
                }
            }
            catch (const std::exception& e)
            {
                MessageBoxA(NULL, e.what(), "ERROR", MB_OK);
            }
            return (INT_PTR)TRUE;

            delete[] bufferId;
            delete[] bufferPassword;
        }
        break;
        case BTN_IMAGEN:
        {
            HWND hImagenEstatica = GetDlgItem(hDlg, STATIC_IMAGE2);
            HWND hImagen = GetDlgItem(hDlg, IMG_USUARIO2);

            OPENFILENAME ofn;
            TCHAR szFile[MAX_PATH] = { 0 };

            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hDlg;
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = _T("Bitmap Files (*.bmp)\0*.bmp\0All Files (*.*)\0*.*\0");
            ofn.nFilterIndex = 1;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn))
            {
                HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, szFile, IMAGE_BITMAP, 95, 95, LR_LOADFROMFILE);
                SetWindowText(hImagenEstatica, szFile);
                SendMessage(hImagen, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);

            }
            return (INT_PTR)TRUE;
        }
        break;
        default:
            return (INT_PTR)FALSE;
        }
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        break;
    case WM_DESTROY:
        return (INT_PTR)FALSE;
        break;
    default:
        return (INT_PTR)FALSE;
    }
}

INT_PTR CALLBACK AgregarArticulo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    PERSONA persona;

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        return (INT_PTR)TRUE;
    }
    break;
    case WM_COMMAND:
        switch (wParam)
        {
        case BTN_CARGARFOTOS:
        {
            HWND hImagenEstatica = GetDlgItem(hDlg, IDC_STATICIMG2);
            HWND hImagenEstatica2 = GetDlgItem(hDlg, IDC_STATICIMG);

            HWND hImagen = GetDlgItem(hDlg, IMG_USUARIO4);
            HWND hImagen2 = GetDlgItem(hDlg, IMG_USUARIO);

            OPENFILENAME ofn;
            TCHAR szFile[MAX_PATH] = { 0 };

            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hDlg;
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = _T("Bitmap Files (*.bmp)\0*.bmp\0All Files (*.*)\0*.*\0");
            ofn.nFilterIndex = 1;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn))
            {
                HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, szFile, IMAGE_BITMAP, 95, 95, LR_LOADFROMFILE);
                SetWindowText(hImagenEstatica, szFile);
                SendMessage(hImagen, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
            }

            SleepEx(30, FALSE);

            OPENFILENAME ofn2;
            TCHAR szFile2[MAX_PATH] = { 0 };

            ZeroMemory(&ofn2, sizeof(ofn2));
            ofn2.lStructSize = sizeof(ofn2);
            ofn2.hwndOwner = hDlg;
            ofn2.lpstrFile = szFile2;
            ofn2.nMaxFile = sizeof(szFile2);
            ofn2.lpstrFilter = _T("Bitmap Files (*.bmp)\0*.bmp\0All Files (*.*)\0*.*\0");
            ofn2.nFilterIndex = 1;
            ofn2.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn2))
            {
                HBITMAP hBitmap2 = (HBITMAP)LoadImage(NULL, szFile2, IMAGE_BITMAP, 95, 95, LR_LOADFROMFILE);
                SetWindowText(hImagenEstatica2, szFile2);
                SendMessage(hImagen2, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap2);
            }
        }break;
        case Art_BTN_INGRESARARTICULO:
        {
            // inicio sesion de Usuario
            HWND hId = GetDlgItem(hDlg, Art_NOMBRE);
            HWND hPassword = GetDlgItem(hDlg, Art_PASSWORD);

            //Articulo
            ARTICULO articulo;
            HWND nombreA = GetDlgItem(hDlg, Art_NOMBREART);
            HWND precioA = GetDlgItem(hDlg, Art_PRECIO);
            HWND marcaA = GetDlgItem(hDlg, Art_MARCA);
            HWND cantidadA = GetDlgItem(hDlg, Art_CANTIDAD);
            HWND foto1A = GetDlgItem(hDlg, IDC_STATICIMG2);
            HWND foto2A = GetDlgItem(hDlg, IDC_STATICIMG);
            HWND descripciconA = GetDlgItem(hDlg, Art_DESCRIPCION);

            if (GetWindowTextLengthA(hId) + 1 > 0 && GetWindowTextLengthA(hPassword) + 1 > 0)
            {
                if (buscarPersona(std::stoi(TextDlg(hId))))
                {
                    if (strcmp(TextDlg(hPassword), buscarP(std::stoi(TextDlg(hId)))->persona.password) == 0 && std::stof(TextDlg(precioA)) > 0 && std::stof(TextDlg(cantidadA)) > 0)
                    {
                        persona = buscarP(std::stoi(TextDlg(hId)))->persona;

                        articulo.IdPersona = persona.ID;
                        articulo.precio = std::stof(TextDlg(precioA));
                        articulo.cantidad = std::stof(TextDlg(cantidadA));
                        if (comprobarNombreArticulo(TextDlg(nombreA))) {

                            strncpy_s(articulo.nombre, TextDlg(nombreA), sizeof(articulo.nombre) - 1);
                            strncpy_s(articulo.descripion, TextDlg(descripciconA), sizeof(articulo.descripion) - 1);
                            strncpy_s(articulo.marca, TextDlg(marcaA), sizeof(articulo.marca) - 1);
                            TCHAR bufferI1[MAX_PATH];
                            GetWindowText(foto1A, bufferI1, MAX_PATH);
                            lstrcpy(articulo.foto1, bufferI1);
                            TCHAR bufferI2[MAX_PATH];
                            GetWindowText(foto2A, bufferI2, MAX_PATH);
                            lstrcpy(articulo.foto2, bufferI2);

                            agregar(articulo);
                            mostrarA(GetDlgItem(hDlg, LB_ARTICULOS), 1, articulo.IdPersona);
                        }
                        else
                        {
                            MessageBoxA(hDlg, "articulo ya existente", "ERROR", MB_OK);
                        }
                    }
                    else
                    {
                        MessageBoxA(hDlg, "contrasena incorrecta", "ERROR", MB_OK);
                    }
                }
                else
                {
                    MessageBoxA(hDlg, "El usuario no existe", "ERROR", MB_OK);
                }
                
            }
            else
            {
                MessageBoxA(hDlg, "ingrese la ID y la contrasena", "ERROR", MB_OK);
            }

            return (INT_PTR)TRUE;
        }break;
        case Art_BTN_BORRARARTICULO:
        {
            HWND hID = GetDlgItem(hDlg, Art_NOMBRE);
            HWND hPassword = GetDlgItem(hDlg, Art_PASSWORD);
            int Size = GetWindowTextLengthA(hPassword) + 1;
            char* bufferPassword = new char[Size];
            HWND hListBox = GetDlgItem(hDlg, LB_ARTICULOS);
            int selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
            if (selectedIndex != LB_ERR)
            {
                int textLength = SendMessage(hListBox, LB_GETTEXTLEN, (WPARAM)selectedIndex, 0);

                if (textLength != LB_ERR)
                {
                    wchar_t* selectedText = new wchar_t[textLength + 1];

                    // Obtiene el contenido de la casilla seleccionada
                    SendMessage(hListBox, LB_GETTEXT, (WPARAM)selectedIndex, (LPARAM)selectedText);

                    wchar_t* numeros = new wchar_t[textLength + 1];
                    for (int i = 2; i < textLength + 1; i++)
                    {
                        if (selectedText[i] >= '0' && selectedText[i] <= '9')
                        {
                            numeros[i - 2] = selectedText[i];
                        }
                        else
                        {
                            numeros[i - 2] = '\0';
                            break;
                        }
                    }
                    try
                    {
                        int x = std::stoi(numeros);
                        int ID;
                        GetWindowTextA(hPassword, bufferPassword, Size);
                        char* comprobarContrasena = new char[Size];
                        comprobarContrasena = buscarP(buscarA(x)->articulo.IdPersona)->persona.password;
                        ID = buscarP(buscarA(x)->articulo.IdPersona)->persona.ID;
                        int comparacion = strcmp(comprobarContrasena, bufferPassword);
                        if (comparacion == 0)
                        {
                            borrarA(x);
                            MessageBox(hDlg, selectedText, L"Se ha borrado el contenido", MB_OK);
                            mostrarA(hListBox, 1, ID);
                        }
                        else
                        {
                            MessageBoxA(hDlg, "La contrasena es incorrecta", "ERROR", MB_OK);
                        }
                    }
                    catch (const std::exception& e)
                    {
                        MessageBoxA(NULL, e.what(), "ERROR", MB_OK);
                    }
                    // Libera la memoria
                    delete[] selectedText;
                    delete[] numeros;
                }
            }
            delete[] bufferPassword;
        }break;
        case Art_BTN_MODIFICARARTICULO:
        {
            if (listaPersona.inicio != NULL) {
                
                // inicio sesion de Usuario
                HWND hId = GetDlgItem(hDlg, Art_NOMBRE);
                HWND hPassword = GetDlgItem(hDlg, Art_PASSWORD);

                //Articulo
                ARTICULO articulo;
                HWND nombreA = GetDlgItem(hDlg, Art_NOMBREART);
                HWND precioA = GetDlgItem(hDlg, Art_PRECIO);
                HWND marcaA = GetDlgItem(hDlg, Art_MARCA);
                HWND cantidadA = GetDlgItem(hDlg, Art_CANTIDAD);
                HWND foto1A = GetDlgItem(hDlg, IDC_STATICIMG2);
                HWND foto2A = GetDlgItem(hDlg, IDC_STATICIMG);
                HWND descripciconA = GetDlgItem(hDlg, Art_DESCRIPCION);


                if (GetWindowTextLengthA(nombreA) + 1 > 1 && GetWindowTextLengthA(precioA) + 1 > 1 && GetWindowTextLengthA(cantidadA) + 1 > 1 && GetWindowTextLengthA(descripciconA) + 1 > 1 && GetWindowTextLengthA(hId) + 1 > 0 && GetWindowTextLengthA(hPassword) + 1 > 0)
                {
                    HWND hListBox = GetDlgItem(hDlg, LB_ARTICULOS);
                    int selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
                    if (selectedIndex != LB_ERR)
                    {
                        int textLength = SendMessage(hListBox, LB_GETTEXTLEN, (WPARAM)selectedIndex, 0);

                        if (textLength != LB_ERR)
                        {
                            wchar_t* selectedText = new wchar_t[textLength + 1];

                            // Obtiene el contenido de la casilla seleccionada
                            SendMessage(hListBox, LB_GETTEXT, (WPARAM)selectedIndex, (LPARAM)selectedText);

                            wchar_t* numeros = new wchar_t[textLength + 1];
                            for (int i = 2; i < textLength + 1; i++)
                            {
                                if (selectedText[i] >= '0' && selectedText[i] <= '9')
                                {
                                    numeros[i - 2] = selectedText[i];
                                }
                                else
                                {
                                    numeros[i - 2] = '\0';
                                    break;
                                }
                            }
                            try
                            {
                                int x = std::stoi(numeros);

                                if (strcmp(TextDlg(hPassword), buscarP(std::stoi(TextDlg(hId)))->persona.password) == 0 && std::stof(TextDlg(precioA)) > 0 && std::stof(TextDlg(cantidadA)) > 0)
                                {
                                    persona = buscarP(std::stoi(TextDlg(hId)))->persona;

                                    articulo.IdPersona = persona.ID;
                                    articulo.precio = std::stof(TextDlg(precioA));
                                    articulo.cantidad = std::stof(TextDlg(cantidadA));
                                    if (comprobarNombreArticulo(TextDlg(nombreA)) || strcmp(buscarA(x)->articulo.nombre, TextDlg(nombreA)) == 0) {

                                        strncpy_s(articulo.nombre, TextDlg(nombreA), sizeof(articulo.nombre) - 1);
                                        strncpy_s(articulo.descripion, TextDlg(descripciconA), sizeof(articulo.nombre) - 1);
                                        strncpy_s(articulo.marca, TextDlg(marcaA), sizeof(articulo.marca) - 1);

                                        TCHAR bufferI1[MAX_PATH];
                                        GetWindowText(foto1A, bufferI1, MAX_PATH);
                                        lstrcpy(articulo.foto1, bufferI1);
                                        TCHAR bufferI2[MAX_PATH];
                                        GetWindowText(foto2A, bufferI2, MAX_PATH);
                                        lstrcpy(articulo.foto2, bufferI2);

                                        modificarA(articulo, x);
                                        mostrarA(hListBox, 1, articulo.IdPersona);
                                    }
                                    else
                                    {
                                        MessageBoxA(hDlg, "articulo ya existente", "ERROR", MB_OK);
                                    }
                                }
                                else
                                {
                                    MessageBoxA(hDlg, "contrasena incorrecta", "ERROR", MB_OK);
                                }
                            }
                            catch (const std::exception& e)
                            {
                                MessageBoxA(hDlg, e.what(), "ERROR", MB_OK);
                            }
                            

                            // Libera la memoria
                            delete[] selectedText;
                            delete[] numeros;
                        }
                    }
                }
                else
                {
                    MessageBoxA(hDlg, "El articulo no pudo ser modificado", "ERROR", MB_OK);
                }
            }
            else
            {
                MessageBoxA(hDlg, "No hay usuarios en la tabla", "ERROR", MB_OK);
            }

        }
        break;
        case IDC_BUTTONMOSTRARUSU:
        {
            // inicio sesion de Usuario
            HWND hId = GetDlgItem(hDlg, Art_NOMBRE);
            HWND hPassword = GetDlgItem(hDlg, Art_PASSWORD);

            if (GetWindowTextLengthA(hId) + 1 > 0 && GetWindowTextLengthA(hPassword) + 1 > 0)
            {
                if (buscarPersona(std::stoi(TextDlg(hId))))
                {
                    if (strcmp(TextDlg(hPassword), buscarP(std::stoi(TextDlg(hId)))->persona.password) == 0)
                    {
                        mostrarA(GetDlgItem(hDlg, LB_ARTICULOS), 1, std::stoi(TextDlg(hId)));
                        HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, buscarP(std::stoi(TextDlg(hId)))->persona.foto, IMAGE_BITMAP, 95, 95, LR_LOADFROMFILE);
                        SendMessage(GetDlgItem(hDlg, IMG_USUARIO5), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
                        SetWindowTextA(GetDlgItem(hDlg, IDC_NOMBRESESION), buscarP(std::stoi(TextDlg(hId)))->persona.nombre);
                        SetWindowTextA(GetDlgItem(hDlg, IDC_EMPRESASESION), buscarP(std::stoi(TextDlg(hId)))->persona.empresa);
                    }
                    else
                    {
                        MessageBoxA(hDlg, "contrasena incorrecta", "ERROR", MB_OK);
                    }
                }
                else
                {
                    MessageBoxA(hDlg, "el usuario no existe", "ERROR", MB_OK);
                }
                
            }
            else
            {
                MessageBoxA(hDlg, "ingrese la ID y la contrasena", "ERROR", MB_OK);
            }

            return (INT_PTR)TRUE;
        }
        break;
        }
        break;
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        break;
    case WM_DESTROY:
        return (INT_PTR)FALSE;
        break;
    default:
        return (INT_PTR)FALSE;
    }
}

INT_PTR CALLBACK Envios(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND hId = GetDlgItem(hDlg, IDC_NOMBRE);
    HWND hPassword = GetDlgItem(hDlg, IDC_PASSWORD);
    HWND hCalle = GetDlgItem(hDlg, IDC_CALLE);
    HWND hColonia = GetDlgItem(hDlg, IDC_COLONIA);
    HWND hCiudad = GetDlgItem(hDlg, IDC_CIUDAD);
    HWND hEstado = GetDlgItem(hDlg, IDC_ESTADO);

    HWND hComboBox = GetDlgItem(hDlg, IDC_COMBO);
    HWND hListBox = GetDlgItem(hDlg, IDC_LISTENVIOS);

    char IdUsuario[255];
    GetWindowTextA(hId, IdUsuario, 255);
    char password[255];
    GetWindowTextA(hPassword, password, 255);
    char calle[255];
    GetWindowTextA(hCalle, calle, 255);
    char colonia[255];
    GetWindowTextA(hColonia, colonia, 255);


    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        return (INT_PTR)TRUE;
    }
    break;
    case WM_COMMAND:
        switch (wParam)
        {
        case IDC_BUTTONINISESION2:
        {
            
            try
            {
                if (sizeof(IdUsuario) > 0 && buscarPersona(std::stoi(IdUsuario)))
                {
                    char* compararPassword = new char[255];
                    compararPassword = buscarP(std::stoi(IdUsuario))->persona.password;
                    PERSONA persona = buscarP(std::stoi(IdUsuario))->persona;

                    int resultado = strcmp(compararPassword, password);

                    if (resultado == 0)
                    {
                        SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_RESETCONTENT, 0, 0);
                        mostrarA(hComboBox, 2, std::stoi(IdUsuario));
                        char buffer[255];
                        sprintf_s(buffer, "%u - %s", persona.ID, persona.nombre);
                        SendMessageA(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)buffer);
                        SendMessageA(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)" ");

                        mostrarE(GetDlgItem(hDlg, IDC_LISTENVIOS), 1, persona.ID);

                        HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, persona.foto, IMAGE_BITMAP, 95, 95, LR_LOADFROMFILE);
                        SendMessage(GetDlgItem(hDlg, IMG_USUARIO), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
                        SetWindowTextA(GetDlgItem(hDlg, IDC_NOMBRESESION), persona.nombre);
                        SetWindowTextA(GetDlgItem(hDlg, IDC_EMPRESASESION), persona.empresa);
                    }
                    else
                    {
                        MessageBoxA(NULL, "contrasena incorrecta", "ERROR", MB_OK);
                    }
                }
                else
                {
                    MessageBoxA(NULL, "datos incorrecta", "ERROR", MB_OK);
                }
            }
            catch (const std::exception& e)
            {
                MessageBoxA(NULL, (LPCSTR)e.what(), "ERROR", MB_OK);
            }
        }
        break;
        case IDC_BUTTONENVIO:
        {
            try
            {
                ENVIO envio, prueba;
                int itemCount = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETCOUNT, 0, 0);
                bool validacion = true;
                
                for (int i = 0; i < itemCount - 2; i++) {

                    int textLength = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXTLEN, i + 2, 0);
                    wchar_t* selectedText = new wchar_t[textLength + 1];
                    SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXT, (WPARAM)i + 2, (LPARAM)selectedText);
                    for (int j = 0; j < textLength; j++)
                    {
                        if (!(selectedText[j] >= '0' && selectedText[j] <= '9'))
                        {
                            selectedText[j] = '\0';
                            break;
                        }
                    }
                    int IdArt = std::stoi(selectedText);
                    int cont = 0;

                    prueba.IdArticulo[i] = IdArt;

                    for (int j = 0; prueba.IdArticulo[j] != 0; j++)
                    {
                        if (prueba.IdArticulo[j] == IdArt)
                        {
                            cont++;
                        }
                    }
                    ARTICULO art = buscarA(IdArt)->articulo;
                    if (art.cantidad < cont)
                    {
                        validacion = false;
                        break;
                    }
                    delete[] selectedText;
                }

                if (validacion)
                {
                    float x = 0;
                    char total[256];
                    for (int i = 0; i < itemCount; i++) {
                        int textLength = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXTLEN, i, 0);


                        wchar_t* selectedText = new wchar_t[textLength + 1];

                        SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXT, (WPARAM)i, (LPARAM)selectedText);
                        if (textLength != LB_ERR) {

                            char sum[1000];
                            for (int j = 0, k = 0, l = 0; j < textLength + 1; j++)
                            {
                                if (i > 1)
                                {
                                    if (j == 0)
                                    {
                                        int it = 0;
                                        char* IdArti = new char[textLength];
                                        while (selectedText[j] != '-' && selectedText[j] != '\0')
                                        {
                                            IdArti[it] = selectedText[j];
                                            j++;
                                            it++;
                                        }
                                        IdArti[it] = '\0';
                                        envio.IdArticulo[i - 2] = std::stoi(IdArti);
                                        delete[] IdArti;
                                        while (!(selectedText[j] >= '0' && selectedText[j] <= '9') && selectedText[j] != '\0')
                                        {
                                            j++;
                                        }

                                    }
                                    if (selectedText[j] >= '0' && selectedText[j] <= '9' || selectedText[j] == '.')
                                    {
                                        sum[k] = selectedText[j];
                                        k++;
                                    }
                                    else
                                    {
                                        sum[k] = '\0';
                                        break;
                                    }
                                }
                            }
                            if (sum[0] > '0' && sum[0] <= '9')
                            {

                                envio.Cantidad++;
                                x += std::stof(sum);
                                ARTICULO art = buscarA(envio.IdArticulo[i - 2])->articulo;
                                art.cantidad--;
                                modificarA(art, art.ID);
                            }
                        }
                    }
                    wchar_t* buffNombre = new wchar_t[255];
                    int textLength = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXTLEN, 0, 0);
                    SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXT, (WPARAM)0, (LPARAM)buffNombre);
                    char Id[255] = { 0 };
                    for (int j = 0; j < textLength + 1; j++)
                    {
                        if (buffNombre[j] >= '0' && buffNombre[j] <= '9')
                        {
                            Id[j] = buffNombre[j];
                        }
                        else
                        {
                            Id[j] = '\0';
                            break;
                        }
                    }
                    envio.Total = x;
                    envio.IdPersona = std::stoi(Id);
                    int it = 0;
                    char buffer[100];
                    GetWindowTextA(GetDlgItem(hDlg, IDC_ESTADO3), buffer, 100);
                    while (obtenerFechaActual(std::stoi(buffer))[it] != '\0')
                    {
                        envio.FechaDeEntrega[it] = obtenerFechaActual(std::stoi(buffer))[it];
                        it++;
                    }
                    if (GetWindowTextLengthA(hCalle) > 1 && GetWindowTextLengthA(hColonia) > 1 && GetWindowTextLengthA(hCiudad) > 1 && GetWindowTextLengthA(hEstado) > 1 && envio.IdArticulo[0] != 0)
                    {
                        GetWindowTextA(hCalle, envio.Calle, GetWindowTextLengthA(hCalle) + 1);
                        GetWindowTextA(hCiudad, envio.Ciudad, GetWindowTextLengthA(hCiudad) + 1);
                        GetWindowTextA(hColonia, envio.Colonia, GetWindowTextLengthA(hColonia) + 1);
                        GetWindowTextA(hEstado, envio.Estado, GetWindowTextLengthA(hEstado) + 1);
                        agregar(envio);
                        mostrarE(GetDlgItem(hDlg, IDC_LISTENVIOS), 1, envio.IdPersona);
                    }
                    else
                    {
                        int y = 0;
                        while (envio.IdArticulo[y] != 0)
                        {
                            ARTICULO art = buscarA(envio.IdArticulo[y])->articulo;
                            art.cantidad++;
                            modificarA(art, art.ID);
                        }
                        MessageBoxA(NULL, "ocurrio un error", "ERROR", MB_OK);
                    }
                }
                else
                {
                    MessageBoxA(NULL, "no hay suficientes articulos para enviar", "ERROR", MB_OK);
                }
            }
            catch (const std::exception& e)
            {
                MessageBoxA(NULL, (LPCSTR)e.what(), "ERROR", MB_OK);
            }
            return (INT_PTR)TRUE;
            
        }
        break;
        case IDC_BUTTONAGREGAR:
        {
            try
            {
                int length = SendMessage(hComboBox, WM_GETTEXTLENGTH, 0, 0);
                char* selectedText = new char[length];
                char numeros[255];

                GetWindowTextA(hComboBox, selectedText, length);

                for (int i = 0; i < length; i++)
                {
                    if (selectedText[i] > '0' && selectedText[i] <= '9')
                    {
                        numeros[i] = selectedText[i];
                    }
                    else
                    {
                        numeros[i] = '\0';
                        break;
                    }
                }
                int x = std::stoi(numeros);
                ARTICULO articulo;
                articulo = buscarA(x)->articulo;
                char buffer[255];
                
                sprintf_s(buffer, "%u - %s (%f)",articulo.ID, articulo.nombre,articulo.precio);
                SendMessageA(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)buffer);

            }
            catch (const std::exception& e)
            {
                MessageBoxA(NULL, (LPCSTR)e.what(), "ERROR", MB_OK);
            }
        }
        break;
        case IDC_BUTTON1: //modificar
        {
            ENVIO envio, prueba;
            int itemCount = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETCOUNT, 0, 0);
            bool validacion = true;

            for (int i = 0; i < itemCount - 2; i++) {

                int textLength = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXTLEN, i + 2, 0);
                wchar_t* selectedText = new wchar_t[textLength + 1];
                SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXT, (WPARAM)i + 2, (LPARAM)selectedText);
                for (int j = 0; j < textLength; j++)
                {
                    if (!(selectedText[j] >= '0' && selectedText[j] <= '9'))
                    {
                        selectedText[j] = '\0';
                        break;
                    }
                }
                int IdArt = std::stoi(selectedText);
                int cont = 0;

                prueba.IdArticulo[i] = IdArt;

                for (int j = 0; prueba.IdArticulo[j] != 0; j++)
                {
                    if (prueba.IdArticulo[j] == IdArt)
                    {
                        cont++;
                    }
                }
                ARTICULO art = buscarA(IdArt)->articulo;
                if (art.cantidad < cont)
                {
                    validacion = false;
                    break;
                }
                delete[] selectedText;
            }

            if(validacion)
            {
                char numeros[255];
                int selecInd = SendMessage(GetDlgItem(hDlg, IDC_LISTENVIOS), LB_GETCURSEL, 0, 0);
                if (selecInd != LB_ERR)
                {
                    int textLen = SendMessage(GetDlgItem(hDlg, IDC_LISTENVIOS), LB_GETTEXTLEN, (WPARAM)selecInd, 0);

                    wchar_t* selecText = new wchar_t[textLen + 1];

                    SendMessage(GetDlgItem(hDlg, IDC_LISTENVIOS), LB_GETTEXT, (WPARAM)selecInd, (LPARAM)selecText);
                    for (int i = 4; i < textLen + 1; i++)
                    {
                        if (selecText[i] >= '0' && selecText[i] <= '9')
                        {
                            numeros[i - 4] = selecText[i];
                        }
                        else
                        {
                            numeros[i - 4] = '\0';
                            break;
                        }
                    }
                    try
                    {

                        int Id = std::stoi(numeros);

                        ENVIO envio = buscarE(Id)->envio;

                        strncpy_s(envio.Calle, TextDlg(GetDlgItem(hDlg, IDC_CALLE)), sizeof(envio.Calle));
                        strncpy_s(envio.Colonia, TextDlg(GetDlgItem(hDlg, IDC_COLONIA)), sizeof(envio.Colonia));
                        strncpy_s(envio.Ciudad, TextDlg(GetDlgItem(hDlg, IDC_CIUDAD)), sizeof(envio.Ciudad));
                        strncpy_s(envio.Estado, TextDlg(GetDlgItem(hDlg, IDC_ESTADO)), sizeof(envio.Estado));
                        strncpy_s(envio.FechaDeEntrega, obtenerFechaActual(std::stoi(TextDlg(GetDlgItem(hDlg, IDC_ESTADO3)))), sizeof(envio.FechaDeEntrega));
                        int cantidadAnterior = envio.Cantidad;
                        int y = 0;

                        while (envio.IdArticulo[y] != 0)
                        {
                            ARTICULO art = buscarA(envio.IdArticulo[y])->articulo;
                            art.cantidad++;
                            modificarA(art, envio.IdArticulo[y]);
                            envio.IdArticulo[y] = 0;
                            y++;
                            envio.Cantidad--;
                            modificarE(envio, envio.ID);
                        }

                        int itemCnt = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETCOUNT, 0, 0);
                        int x = 0;

                        for (int i = 0; i < itemCnt - 2; i++) {

                            int textLength = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXTLEN, i + 2, 0);
                            wchar_t* selectedText = new wchar_t[textLength + 1];
                            SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXT, (WPARAM)i + 2, (LPARAM)selectedText);
                            for (int j = 0; j < textLength; j++)
                            {
                                if (!(selectedText[j] >= '0' && selectedText[j] <= '9'))
                                {
                                    selectedText[j] = '\0';
                                    break;
                                }
                            }
                            int IdArt = std::stoi(selectedText);
                            envio.IdArticulo[i] = IdArt;
                            x += buscarA(IdArt)->articulo.precio;
                            envio.Cantidad++;
                            ARTICULO art = buscarA(IdArt)->articulo;
                            art.cantidad--;
                            modificarA(art, IdArt);
                            delete[] selectedText;
                        }
                        envio.Total = x;
                        modificarE(envio, envio.ID);
                        mostrarE(GetDlgItem(hDlg, IDC_LISTENVIOS), 1, envio.IdPersona);
                        char buff[255];
                        sprintf_s(buff, "ID: %u", envio.ID);
                        MessageBoxA(hDlg, buff, "Envio modificado", MB_OK);
                    }
                    catch (const std::exception& e)
                    {
                        MessageBoxA(NULL, (LPCSTR)e.what(), "ERROR", MB_OK);
                    }
                    delete[] selecText;
                }
            }
            else
            {
                MessageBoxA(NULL, "no hay suficientes articulos para enviar", "ERROR", MB_OK);
            }

            return (INT_PTR)TRUE;
        }
        break;
        case IDC_BUTTON2: //borrar
        {
            char numeros[255];
            int selecInd = SendMessage(GetDlgItem(hDlg, IDC_LISTENVIOS), LB_GETCURSEL, 0, 0);
            if (selecInd != LB_ERR)
            {
                int textLen = SendMessage(GetDlgItem(hDlg, IDC_LISTENVIOS), LB_GETTEXTLEN, (WPARAM)selecInd, 0);

                wchar_t* selecText = new wchar_t[textLen + 1];

                SendMessage(GetDlgItem(hDlg, IDC_LISTENVIOS), LB_GETTEXT, (WPARAM)selecInd, (LPARAM)selecText);
                for (int i = 4; i < textLen + 1; i++)
                {
                    if (selecText[i] > '0' && selecText[i] <= '9')
                    {
                        numeros[i - 4] = selecText[i];
                    }
                    else
                    {
                        numeros[i - 4] = '\0';
                        break;
                    }
                }

                try
                {
                    int Id = std::stoi(numeros);

                    ENVIO envio = buscarE(Id)->envio;

                    int y = 0;
                    while (envio.IdArticulo[y] != 0)
                    {
                        ARTICULO art = buscarA(envio.IdArticulo[y])->articulo;
                        art.cantidad++;
                        modificarA(art, envio.IdArticulo[y]);
                        envio.IdArticulo[y] = 0;
                        y++;
                        envio.Cantidad--;
                    }

                    borrarE(envio.ID);

                    mostrarE(GetDlgItem(hDlg, IDC_LISTENVIOS), 1, envio.IdPersona);
                }
                catch (const std::exception& e)
                {
                    MessageBoxA(NULL, (LPCSTR)e.what(), "ERROR", MB_OK);
                }
            }

        }
        default:
            return (INT_PTR)TRUE;
            break;
        }
        break;
        
        break;
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        break;
    case WM_DESTROY:
        return (INT_PTR)FALSE;
        break;
    default:
        return (INT_PTR)FALSE;
    }
}

void agregar(PERSONA persona) 
{
    NODO_PERSONA* nuevoNodo = new NODO_PERSONA;
    nuevoNodo->persona = persona;
    // Verificar si la lista está vacía
    if (listaPersona.inicio == nullptr) {
        nuevoNodo->persona.ID = 1;
        listaPersona.inicio = nuevoNodo;
        listaPersona.fin = listaPersona.inicio;
        listaPersona.fin->siguiente = nullptr;
        listaPersona.inicio->anterior = nullptr;
    }
    else {
        NODO_PERSONA* i = new NODO_PERSONA;
        i = listaPersona.inicio;
        while (i->siguiente != nullptr)
        {
            i = i->siguiente;
        }
        i->siguiente = nuevoNodo;
        nuevoNodo->anterior = i;
        nuevoNodo->persona.ID = nuevoNodo->anterior->persona.ID + 1;
        listaPersona.fin = nuevoNodo;
    }
    listaPersona.cantidad++;
}
void agregar(ARTICULO articulo) {
    NODO_ARTICULO* nuevoNodo = new NODO_ARTICULO;
    nuevoNodo->articulo = articulo;
    // Verificar si la lista está vacía
    if (listaArticulo.inicio == nullptr) {
        nuevoNodo->articulo.ID = 1;
        listaArticulo.inicio = nuevoNodo;
        listaArticulo.fin = listaArticulo.inicio;
        listaArticulo.fin->siguiente = nullptr;
        listaArticulo.inicio->anterior = nullptr;
    }
    else {
        NODO_ARTICULO* i = new NODO_ARTICULO;
        i = listaArticulo.inicio;
        while (i->siguiente != nullptr)
        {
            i = i->siguiente;
        }
        i->siguiente = nuevoNodo;
        nuevoNodo->anterior = i;
        nuevoNodo->articulo.ID = nuevoNodo->anterior->articulo.ID + 1;
        listaArticulo.fin = nuevoNodo;
    }
    listaArticulo.cantidad++;
}
void agregar(ENVIO envio) {
    NODO_ENVIO* nuevoNodo = new NODO_ENVIO;
    nuevoNodo->envio = envio;
    // Verificar si la lista está vacía
    if (listaEnvio.inicio == nullptr) {
        nuevoNodo->envio.ID = 1;
        listaEnvio.inicio = nuevoNodo;
        listaEnvio.fin = listaEnvio.inicio;
        listaEnvio.fin->siguiente = nullptr;
        listaEnvio.inicio->anterior = nullptr;
    }
    else {
        NODO_ENVIO* i = new NODO_ENVIO;
        i = listaEnvio.inicio;
        while (i->siguiente != NULL)
        {
            i = i->siguiente;
        }
        i->siguiente = nuevoNodo;
        nuevoNodo->anterior = i;
        nuevoNodo->envio.ID = nuevoNodo->anterior->envio.ID + 1;
        listaEnvio.fin = nuevoNodo;
    }
    listaEnvio.cantidad++;
}

NODO_PERSONA* buscarP(int Id)
{
    NODO_PERSONA* i = new NODO_PERSONA;
    i = listaPersona.inicio;
    while (i->persona.ID != Id && i != nullptr)
    {
        i = i->siguiente;
    }
    return i;
}
NODO_ARTICULO* buscarA(int Id)
{
    NODO_ARTICULO* i = new NODO_ARTICULO;
    i = listaArticulo.inicio;
    while (i->articulo.ID != Id && i != NULL)
    {
        i = i->siguiente;
    }
    return i;
}


void borrarP(int Id) 
{
    NODO_PERSONA* buscar = buscarP(Id);
    if (buscar != nullptr)
    {
        NODO_PERSONA* anteriorBuscar = buscar->anterior;
        NODO_PERSONA* siguienteBuscar = buscar->siguiente;
        if (buscar->anterior == NULL) 
        {
            listaPersona.inicio = listaPersona.inicio->siguiente;
            if (listaPersona.fin == buscar)
                listaPersona.fin = NULL;
        }
        else if (buscar->siguiente == NULL) 
        {
            anteriorBuscar->siguiente = NULL;
            listaPersona.fin = anteriorBuscar;
        }
        else {
            anteriorBuscar->siguiente = siguienteBuscar;
            siguienteBuscar->anterior = anteriorBuscar;
        }
        delete buscar;
        listaPersona.cantidad = listaPersona.cantidad - 1;
    }
    else
    {
        MessageBoxA(NULL, "no se pudo encontrar un usuario con ese ID", "ERROR", MB_OK);
    }
}


void borrarA(int Id)
{
    NODO_ARTICULO* buscar = buscarA(Id);
    if (buscar != nullptr)
    {
        NODO_ARTICULO* anteriorBuscar = buscar->anterior;
        NODO_ARTICULO* siguienteBuscar = buscar->siguiente;
        if (buscar->anterior == NULL)
        {
            listaArticulo.inicio = listaArticulo.inicio->siguiente;
            if (listaArticulo.fin == buscar)
                listaArticulo.fin = NULL;
        }
        else if (buscar->siguiente == NULL)
        {
            anteriorBuscar->siguiente = NULL;
            listaArticulo.fin = anteriorBuscar;
        }
        else {
            anteriorBuscar->siguiente = siguienteBuscar;
            siguienteBuscar->anterior = anteriorBuscar;
        }
        delete buscar;
        listaArticulo.cantidad = listaArticulo.cantidad - 1;
    }
    else
    {
        MessageBoxA(NULL, "no se pudo encontrar un articulo con ese ID", "ERROR", MB_OK);
    }
}

void borrarE(int Id) {
    NODO_ENVIO* buscar = buscarE(Id);
    if (buscar != nullptr)
    {
        NODO_ENVIO* anteriorBuscar = buscar->anterior;
        NODO_ENVIO* siguienteBuscar = buscar->siguiente;
        if (buscar->anterior == NULL)
        {
            listaEnvio.inicio = listaEnvio.inicio->siguiente;
            if (listaEnvio.fin == buscar)
                listaEnvio.fin = NULL;
        }
        else if (buscar->siguiente == NULL)
        {
            anteriorBuscar->siguiente = NULL;
            listaEnvio.fin = anteriorBuscar;
        }
        else {
            anteriorBuscar->siguiente = siguienteBuscar;
            siguienteBuscar->anterior = anteriorBuscar;
        }
        delete buscar;
        listaEnvio.cantidad = listaEnvio.cantidad - 1;
    }
    else
    {
        MessageBoxA(NULL, "no se pudo encontrar un envio con ese ID", "ERROR", MB_OK);
    }
}

void mostrarP(HWND h,int opc) 
{
    SendMessage(h, LB_RESETCONTENT, 0, 0);
    NODO_PERSONA* i = new NODO_PERSONA;
    i = listaPersona.inicio;

    while (i != NULL)
    {
        mostrarObjetoP(h, i->persona, opc);
        i = i->siguiente;
    }
}

void mostrarA(HWND h, int opc, int id)
{
    if (opc == 1)
    {
        SendMessage(h, LB_RESETCONTENT, 0, 0);
    }
    if (opc == 2)
    {
        SendMessage(h, CB_RESETCONTENT, 0, 0);
    }

    NODO_ARTICULO* i = new NODO_ARTICULO;
    i = listaArticulo.inicio;
    if (opc == 1)
    {
        mostrarObjetoP(h, buscarP(id)->persona, 1);
        SendMessageA(h, LB_ADDSTRING, 0, (LPARAM)"");
    }

    while (i != NULL)
    {
        if (i->articulo.IdPersona == id)
        {
            mostrarObjetoA(h, i->articulo, opc);
        }
        i = i->siguiente;
    }
}

void mostrarE(HWND h, int opc, int id)
{
    SendMessage(h, LB_RESETCONTENT, 0, 0);

    NODO_ENVIO* i = new NODO_ENVIO;
    i = listaEnvio.inicio;

    mostrarObjetoP(h, buscarP(id)->persona, 1);
    SendMessageA(h, LB_ADDSTRING, 0, (LPARAM)"");

    while (i != NULL)
    {
        if (i->envio.IdPersona == id)
        {
            mostrarObjetoE(h, i->envio, opc);
            i = i->siguiente;
        }
    }
}

void mostrarObjetoP(HWND hwnd, PERSONA persona,int opc)
{
    switch (opc)
    {
    case 1: // listBox
    {
        char textoPersona[1024];
        sprintf_s(textoPersona, "%d - %s [ %s ]", persona.ID, persona.nombre, persona.empresa);

        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoPersona);

    }
        break;
    case 2: // comboBox
    {
        char textoPersona[1024];
        sprintf_s(textoPersona, "%d - %s [ %s ]", persona.ID, persona.nombre, persona.empresa);

        SendMessageA(hwnd, CB_ADDSTRING, 0, (LPARAM)textoPersona);
    }
        break;
    default:
        MessageBoxA(NULL, "no se encontro esa opcion", "ERROR", MB_OK);
        break;
    }
}

void mostrarObjetoA(HWND hwnd, ARTICULO articulo, int opc)
{
    switch (opc)
    {
    case 1: // listBox
    {
        char textoArticulo[1024];
        char textoMarca[1024];
        char textoPrecico[1024];
        char textoDescripcion[1024];
        sprintf_s(textoArticulo, "[ %u ]", articulo.ID);
        sprintf_s(textoMarca, "   %s | %s ", articulo.nombre, articulo.marca);
        sprintf_s(textoPrecico, "   %f $", articulo.precio);
        sprintf_s(textoDescripcion, "   %s", articulo.descripion);
        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoArticulo);
        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoMarca);
        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoPrecico);
        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoDescripcion);
        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)"");
    }
    break;
    case 2: // comboBox
    {
        char textoArticulo[1024];
        sprintf_s(textoArticulo, "%u - %s [ %f ]", articulo.ID, articulo.nombre, articulo.precio);

        SendMessageA(hwnd, CB_ADDSTRING, 0, (LPARAM)textoArticulo);
    }
    break;
    default:
        MessageBoxA(NULL, "no se encontro esa opcion", "ERROR", MB_OK);
        break;
    }
}

void mostrarObjetoE(HWND hwnd, ENVIO envio, int opc)
{
    switch (opc)
    {
    case 1: // listBox
    {
        char textoEnvio1[1024];
        char textoEnvio2[1024];
        char textoEnvio3[1024];
        char textoEnvio4[1024];
        char textoEnvio5[1024];
        char textoEnvio6[1024];
        char textoEnvio7[1024];
        sprintf_s(textoEnvio1, "ID: %u", envio.ID);
        sprintf_s(textoEnvio2, "Calle %s", envio.Calle);
        sprintf_s(textoEnvio3, "Colonia %s", envio.Colonia);
        sprintf_s(textoEnvio4, "Ciudad %s", envio.Ciudad);
        sprintf_s(textoEnvio5, "Estado %s", envio.Estado);
        sprintf_s(textoEnvio6, "Fecha de entrega: %s", envio.FechaDeEntrega);
        sprintf_s(textoEnvio7, "TOTAL - %f", envio.Total);
        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoEnvio1);
        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoEnvio2);
        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoEnvio3);
        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoEnvio4);
        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoEnvio5);
        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoEnvio6); 
        int i = 0;
        while (envio.IdArticulo[i] != 0)
        {
            char textoEnvio[1024];
            sprintf_s(textoEnvio, "     [%u] %s - %f", envio.IdArticulo[i], buscarA(envio.IdArticulo[i])->articulo.nombre, buscarA(envio.IdArticulo[i])->articulo.precio);
            SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoEnvio);
            i++;
        }
        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoEnvio7);
        SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)"");

        //char textoEnvio8[1024];
        //if (ordenarPorFecha(envio.ID))
        //{

        //    sprintf_s(textoEnvio8, "[ ENTREGADO ]");
        //    SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoEnvio8);
        //}
        //else
        //{

        //    sprintf_s(textoEnvio8, "[ PENDIENTE ]");
        //    SendMessageA(hwnd, LB_ADDSTRING, 0, (LPARAM)textoEnvio8);
        //}
    }
    break;
    case 2: // comboBox
    {
        char textoEnvio[1024];
        sprintf_s(textoEnvio, "%u - %s - %s - %f", envio.ID, envio.Calle, envio.Colonia, envio.Total);

        SendMessageA(hwnd, CB_ADDSTRING, 0, (LPARAM)textoEnvio);
    }
    break;
    default:
        MessageBoxA(NULL, "no se encontro esa opcion", "ERROR", MB_OK);
        break;
    }
}


bool contieneSoloLetras(char* str) {
    int size = 0;
    while (str[size] != '\0')
    {
        if (str[size] == ' ')
        {

        }
        else
        {
            if (!std::isalpha(str[size]))
            {
                return false;
            }
        }
        size++;
    } 
    return true;
}

void convertirAMayusculas(char* str) {
    int size = 0;
    while (str[size] != '\0')
    {
        str[size] = std::toupper(str[size]);
        size++;
    }
}

NODO_ENVIO* buscarE(int Id)
{
    NODO_ENVIO* i = new NODO_ENVIO;
    i = listaEnvio.inicio;
    while (i->envio.ID != Id && i != NULL)
    {
        i = i->siguiente;
    }
    return i;
}


void modificarP(PERSONA persona, int Id)
{
    NODO_PERSONA* buscar = buscarP(Id);
    if (buscar != NULL) {
        strcpy_s(buscar->persona.nombre, 255, persona.nombre);
        strcpy_s(buscar->persona.empresa, 255, persona.empresa);
        strcpy_s(buscar->persona.password, 255, persona.password);
        lstrcpy(buscar->persona.foto, persona.foto);
    }
}

void modificarA(ARTICULO articulo, int Id)
{
    NODO_ARTICULO* buscar = buscarA(Id);
    if (buscar != NULL) {
        strcpy_s(buscar->articulo.nombre, 255, articulo.nombre);
        buscar->articulo.precio = articulo.precio;
        buscar->articulo.cantidad = articulo.cantidad;
        lstrcpy(buscar->articulo.foto1, articulo.foto1);
        lstrcpy(buscar->articulo.foto2, articulo.foto2);
        strcpy_s(buscar->articulo.descripion, 255, articulo.descripion);
        strcpy_s(buscar->articulo.marca, 255, articulo.marca);
    }
}

void modificarE(ENVIO envio, int Id)
{
    NODO_ENVIO* buscar = buscarE(Id);
    if (buscar != NULL) {
        strcpy_s(buscar->envio.Calle, 255, envio.Calle);
        strcpy_s(buscar->envio.Colonia, 255, envio.Colonia);
        strcpy_s(buscar->envio.Ciudad, 255, envio.Ciudad);
        strcpy_s(buscar->envio.Estado, 255, envio.Estado);
        strcpy_s(buscar->envio.FechaDeEntrega, 255, envio.FechaDeEntrega); 
        int i = 0;
        while (buscar->envio.IdArticulo[i] != 0 || envio.IdArticulo[i] != 0)
        {
            buscar->envio.IdArticulo[i] = envio.IdArticulo[i];
            i++;
        }
        buscar->envio.IdPersona = envio.IdPersona;
        buscar->envio.Total = envio.Total;
        buscar->envio.Cantidad = envio.Cantidad;
    }
}




void guardarLista() {
    std::ofstream archivoP("C:\\Users\\Tibs\\source\\repos\\ProyectoProgAv_1956352\\ProyectoProgAv_1956352\\Personas.bin", std::ios::binary | std::ios::trunc | std::ios::out);
    if (archivoP.is_open()) {
        NODO_PERSONA* indiceP = listaPersona.inicio;
        while (indiceP != NULL) {
            archivoP.write((char*)indiceP, sizeof(NODO_PERSONA));
            indiceP = indiceP->siguiente;
        }
    }
    else {
        MessageBoxA(NULL, "no se pudo guardar el archivo", "ERROR", MB_OK);
    }
    archivoP.close();
    std::ofstream archivoA("C:\\Users\\Tibs\\source\\repos\\ProyectoProgAv_1956352\\ProyectoProgAv_1956352\\Articulos.bin", std::ios::binary | std::ios::trunc | std::ios::out);
    if (archivoA.is_open())
    {
        NODO_ARTICULO* indiceA = listaArticulo.inicio;
        while (indiceA != NULL) {
            archivoA.write((char*)indiceA, sizeof(NODO_ARTICULO));
            indiceA = indiceA->siguiente;
        }
    }
    else
    {
        MessageBoxA(NULL, "no se pudo guardar el archivo", "ERROR", MB_OK);
    }
    archivoA.close();
    std::ofstream archivoE("C:\\Users\\Tibs\\source\\repos\\ProyectoProgAv_1956352\\ProyectoProgAv_1956352\\Envios.bin", std::ios::binary | std::ios::trunc | std::ios::out);
    if (archivoE.is_open())
    {
        NODO_ENVIO* indiceE = listaEnvio.inicio;
        while (indiceE != NULL) {
            archivoE.write((char*)indiceE, sizeof(NODO_ENVIO));
            indiceE = indiceE->siguiente;
        }
    }
    else
    {
        MessageBoxA(NULL, "no se pudo guardar el archivo", "ERROR", MB_OK);
    }
    archivoE.close();
}

void cargarLista() {
    std::ifstream archivoP("Personas.bin", std::ios::binary | std::ios::in | std::ios::ate);
    if (archivoP.is_open()) 
    {
        int archivoTamanio = archivoP.tellg();
        archivoP.seekg(std::ios::beg);
        int bytesLeidos = 0;
        while (bytesLeidos < archivoTamanio) {
            NODO_PERSONA lectura;
            archivoP.read((char*)&lectura, sizeof(NODO_PERSONA));
            agregar(lectura.persona);
            bytesLeidos += sizeof(NODO_PERSONA);
        }
    }
    else {
        MessageBoxA(NULL, "no se pudo cargar el archivo", "ERROR", MB_OK);
    }
    archivoP.close();
    std::ifstream archivoA("Articulos.bin", std::ios::binary | std::ios::in | std::ios::ate);
    if (archivoA.is_open())
    {
        int archivoTamanio = archivoA.tellg();
        archivoA.seekg(std::ios::beg);
        int bytesLeidos = 0;
        while (bytesLeidos < archivoTamanio) {
            NODO_ARTICULO lectura;
            archivoA.read((char*)&lectura, sizeof(NODO_ARTICULO));
            agregar(lectura.articulo);
            bytesLeidos += sizeof(NODO_PERSONA);
        }
    }
    else
    {
        MessageBoxA(NULL, "no se pudo cargar el archivo", "ERROR", MB_OK);
    }
    archivoA.close();
    std::ifstream archivoE("Envios.bin", std::ios::binary | std::ios::in | std::ios::ate);
    if (archivoE.is_open())
    {
        int archivoTamanio = archivoE.tellg();
        archivoE.seekg(std::ios::beg);
        int bytesLeidos = 0;
        while (bytesLeidos < archivoTamanio) {
            NODO_ENVIO lectura;
            archivoE.read((char*)&lectura, sizeof(NODO_ENVIO));
            agregar(lectura.envio);
            bytesLeidos += sizeof(NODO_ENVIO);
        }
    }
    else
    {
        MessageBoxA(NULL, "no se pudo cargar el archivo", "ERROR", MB_OK);
    }
    archivoE.close();
}

char* TextDlg(HWND objeto) {

    int size = GetWindowTextLengthA(objeto) + 1;
    char* buffer = new char[size];
    GetWindowTextA(objeto,buffer,size);
    return buffer;
}

bool comprobarNombreArticulo(char* str) {
    if (listaArticulo.inicio != NULL)
    {
        NODO_ARTICULO* index = new NODO_ARTICULO;
        index = listaArticulo.inicio;
        while (index->siguiente != NULL)
        {
            if (strcmp(index->articulo.nombre, str) == 0)
            {
                return false;
            }

            index = index->siguiente;
        }
        if (strcmp(listaArticulo.fin->articulo.nombre, str) == 0)
        {
            return false;
        }
    }
    
    return true;
}

char* obtenerFechaActual(int dias) {
    std::chrono::system_clock::time_point hoy = std::chrono::system_clock::now();
    std::chrono::hours hoursToAdd(24 * dias);

    std::chrono::system_clock::time_point FechaEntrega = hoy + hoursToAdd;

    std::time_t futureTime = std::chrono::system_clock::to_time_t(FechaEntrega);
    std::tm localTime;

    localtime_s(&localTime, &futureTime);
    char time[255];
    int year = localTime.tm_year + 1900;
    int month = localTime.tm_mon;
    int day = localTime.tm_mday;
    char bufferMonth[3] = {'0','0'};
    char bufferDay[3] = { '0','0' };

    if (month < 10) {
        bufferMonth[0] = '0';
        bufferMonth[1] = '0' + (month + 1);
        bufferMonth[2] = '\0';
    }
    else {
        bufferMonth[0] = '0' + ((month + 1) / 10);
        bufferMonth[1] = '0' + ((month + 1) % 10);
        bufferMonth[2] = '\0';
    }

    if (day < 10) {
        bufferDay[0] = '0';
        bufferDay[1] = '0' + day;
        bufferDay[2] = '\0';
    }
    else {
        bufferDay[0] = '0' + (day / 10);
        bufferDay[1] = '0' + (day % 10);
        bufferDay[2] = '\0';
    }

    sprintf_s(time, "%u / %s / %s", year, bufferMonth, bufferDay);
    
    return time;
   
}

bool buscarPersona(int id) {
    NODO_PERSONA* index = new NODO_PERSONA;
    index = listaPersona.inicio;
    while (index->siguiente != NULL)
    {
        if (index->persona.ID == id)
        {
            return true;
        }
        index = index->siguiente;
    }
    if (listaPersona.fin->persona.ID == id)
    {
        return true;
    }
    return false;
}
bool buscarArticulo(int id) {
    NODO_ARTICULO* index = new NODO_ARTICULO;
    index = listaArticulo.inicio;
    while (index->siguiente != NULL)
    {
        if (index->articulo.ID == id)
        {
            return true;
        }
        index = index->siguiente;
    }
    if (listaArticulo.fin->articulo.ID == id)
    {
        return true;
    }
    return false;
}
bool buscarEnvio(int id) {
    NODO_ENVIO* index = new NODO_ENVIO;
    index = listaEnvio.inicio;
    while (index->siguiente != NULL)
    {
        if (index->envio.ID == id)
        {
            return true;
        }
        index = index->siguiente;
    }
    if (listaEnvio.fin->envio.ID == id)
    {
        return true;
    }
    return false;
}


//bool ordenarPorFecha(int id) {
//    NODO_ENVIO* indx = new NODO_ENVIO;
//    indx = buscarE(id);
//        char cYear[5] = { '\0' };
//        char cMonth[3] = { '\0' };
//        char cDay[3] = {'\0'};
//        int year = 0;
//        int month = 0;
//        int day = 0;
//        int yearToday = 0;
//        int monthToday = 0;
//        int dayToday = 0;
//        
//        cYear[0] = indx->envio.FechaDeEntrega[0];
//        cYear[1] = indx->envio.FechaDeEntrega[1];
//        cYear[2] = indx->envio.FechaDeEntrega[2];
//        cYear[3] = indx->envio.FechaDeEntrega[3];
//        cYear[4] = '\0';
//
//        cMonth[0] = indx->envio.FechaDeEntrega[7];
//        cMonth[1] = indx->envio.FechaDeEntrega[8];
//        cMonth[2] = '\0';
//
//        cDay[0] = indx->envio.FechaDeEntrega[12];
//        cDay[1] = indx->envio.FechaDeEntrega[13];
//        cDay[2] = '\0';
//
//        year = std::stoi(cYear);
//        month = std::stoi(cMonth);
//        day = std::stoi(cDay);
//
//        char fechahoy[14];
//        for (int i = 0; i < 14; i++)
//        {
//            fechahoy[i] = obtenerFechaActual(0)[i];
//        }
//
//        cYear[0] = fechahoy[0];
//        cYear[1] = fechahoy[1];
//        cYear[2] = fechahoy[2];
//        cYear[3] = fechahoy[3];
//
//        cMonth[0] = fechahoy[7];
//        cMonth[1] = fechahoy[8];
//
//        cDay[0] = fechahoy[12];
//        cDay[1] = fechahoy[13];
//
//        yearToday = std::stoi(cYear);
//        monthToday = std::stoi(cMonth);
//        dayToday = std::stoi(cDay);
//
//        if (year >= yearToday && month >= monthToday && day >= dayToday) 
//        {
//            return true;
//        }
//        else
//        {
//            return false;
//        }
//}