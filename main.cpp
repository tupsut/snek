/*
####################################################################
# TIE-02201 Ohjelmointi 2: Perusteet, K2019                        #
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project4: snek: The Revengeance                                  #
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: main.cpp                                                   #
# Description: Starts executing the program.                       #
#                                                                  #
# Author: Saskia Simisker, 282598, saskia.simisker@tuni.fi         #
####################################################################
*/

#include "main_window.hh"
#include <QApplication>


int main(int argc, char** argv) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
