/**
 * Application: AbstractGraph
 * Module: GUI
 * File: main.cpp
 * Description: Main entry point to GUI frontend of Abstract graph
 *              application
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id: main.cpp 13 2012-03-31 18:46:19Z Dennis.McWherter@gmail.com $
 */

#ifdef _WIN32
#include <Windows.h>
#endif

#include <QApplication>

#include "Windows/MainWindow.h"

int runApplication(int argc, char* argv[]);

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpstr, int nCmd)
{
  return runApplication(0, NULL);
}
#else
int main(int argc, char* argv[])
{
  return runApplication(argc, argv);
}
#endif

int runApplication(int argc, char* argv[])
{
  QApplication app(argc, argv);
  MainWindow window("AbstractGraph");
  window.resize(800, 600);
  window.show();
  return app.exec();
}
