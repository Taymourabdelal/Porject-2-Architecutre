//////
//////  PARSETRIAL.cpp
//////  Project_2_ARCHI
//////
//////  Created by Menna  Dessokey on 12/2/18.
//////  Copyright © 2018 Menna  Dessokey. All rights reserved.
//////
////
////#include "PARSETRIAL.hpp"
////void Parsethree(string instruction, string& Rd, string& RS1, string& RS2)
////{
////    ;
////}
////
////  main.cpp
////  project2 architecture
////
////  Created by Maha Moussa on 12/2/18.
////  Copyright © 2018 Maha Moussa. All rights reserved.
////
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//using namespace std;
//struct Memory
//{
//    int address;
//    string item; // the ittem here can be botht the instruciton and the data
//};
//
//
//
//
//
//
//
//
//
//int main(int argc, const char * argv[]) {
//    int selection;
//    ifstream instfile;
//    string fileline;
//    vector<Memory> instkeeper;
//
//
//
//
//    cout<<endl<<"How do you want to enter the instructions?"<<endl<<"Enter 0 for a file, 1 for individual insstructions, 2 for a selection."<<endl;
//    cin>>selection;
//
//
//
//    if ( selection == 0) // the user selected a file
//    {
//        Memory object; // object in memory to be entered in the vector
//        int starting_address, instruction_number, Data_start, flag; // the starting address and the counter and the number after which tthe data starts and the answer of the user
//        bool Data_Done = false ; // whether he finished entering the data or not.
//        string Data;
//        int Data_address;
//
//
//
//
//        cout<<"please choose a starting address"<<endl;
//        cin>>starting_address;
//        instruction_number = starting_address;
//        instfile.open("/Users/mennadessokey/Desktop/AUC/sem 5/ARCHI/Project_2_ARCHI/Project_2_ARCHI/PROGRAM");
//        if (instfile.fail())
//            cout<<" the file has failed to open";
//        else {
//            getline(instfile, fileline);
//            object.item = fileline;
//            object.address = starting_address;
//            cout<<endl;
//            instkeeper.push_back(object);
//            cout<<endl<<object.address<<endl<<object.item;
//            while(!instfile.eof())
//            {
//                instruction_number++;
//                getline(instfile, fileline);
//                object.item = fileline;
//                object.address= instruction_number;
//                instkeeper.push_back(object);
//                cout<<endl<<object.address<<endl<<object.item;
//                //cout<< " tthis is the file line" << fileline<<"done" <<endl;
//
//            }
//            Data_start = instruction_number + 1; // the data will start drom the one after the instruction.
//
//            while (!Data_Done)
//            {
//                cout<<"please enter the data and then its address"<<endl;
//                cin >> Data;
//                cout<<endl;
//                cin>> Data_address;
//                while (Data_address <= instruction_number)
//                {
//                    cout<<" This is an invalid address renter the address "<<endl;
//                    cin>>Data_address;
//                }
//                object.address = Data_address;
//                object.item = Data;
//                instkeeper.push_back(object);
//                cout<<endl<<"this is the address "<<object.address<<endl<<"this is the data "<<object.item<<endl;
//                cout<<"do you wantt to enter more data? 0 for no and 1 for yes"<<endl;
//                cin>>flag;
//                if (flag == 0)
//                    Data_Done = true;
//
//                // Data_start++;
//            }
//        }
//
//
//    }
//
//
//
//
//    else if (selection == 1) // the user selcting entering instructio individually
//    {
//        Memory object; // object in memory to be entered in the vector
//        int starting_address, instruction_number, Data_start, flag; // the starting address and the counter and the number after which tthe data starts and the answer of the user
//        bool Data_Done = false ; // whether he finished entering the data or not.
//        string Data;
//        int Data_address;
//
//        bool Done = false; // when the user is done the done flag will be true
//        string instruction;
//        int repeat;
//        cout<<"please enter the starting address";
//        cin>>starting_address;
//        instruction_number = starting_address;
//        do
//        {
//            object.address = instruction_number;
//            cout<<endl<<"Please enter instruction"<<endl;
//            cin.ignore();
//            getline ( cin ,  instruction);
//            object.item = instruction;
//            cout<<endl;
//            instkeeper.push_back(object);
//            cout<<endl<<"this is the address "<<object.address<<endl<<"this is the data "<<object.item<<endl;
//            cout<<endl<<"do you want to enter another instruction; 0 for no 1 for yes"<<endl;
//            cin>>repeat;
//            if (repeat)
//            {
//                Done = false;
//                instruction_number++;
//            }
//
//            else
//                Done = true;
//
//
//        }while (!Done);
//
//        Data_start = instruction_number + 1; // the data will start drom the one after the instruction.
//
//        while (!Data_Done)
//        {
//            cout<<"please enter the data and then its address"<<endl;
//            cin >> Data;
//            cout<<endl;
//            cin>> Data_address;
//            while (Data_address <= instruction_number)
//            {
//                cout<<" This is an invalid address renter the address "<<endl;
//                cin>>Data_address;
//            }
//            object.address = Data_address;
//            object.item = Data;
//            instkeeper.push_back(object);
//            cout<<endl<<"this is the address "<<object.address<<endl<<"this is the data "<<object.item<<endl;
//            cout<<"do you wantt to enter more data? 0 for no and 1 for yes"<<endl;
//            cin>>flag;
//            if (flag == 0)
//                Data_Done = true;
//
//            // Data_start++;
//        }
//
//    }
//
//
//
//
//
//
//
//
//    else if (selection == 2) // the user selected a selection of lines
//    {
//        instfile.open("/Users/mahamoussa/Desktop/architecture/project2 architecture/project2 architecture/instfile.txt");
//        if (instfile.fail())
//            cout<<" the file has failed to open";
//        else {
//            getline(instfile, fileline);
//            cout<<endl;
//            while(!instfile.eof())
//            {
//                getline(instfile, fileline);
//                cout<< fileline<<endl;
//            }
//        }
//    }
//    instfile.close();
//    return 0;
//}

