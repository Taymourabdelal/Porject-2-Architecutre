//
//  main.cpp
//  project2 architecture
//
//  Created by Maha Moussa on 12/2/18.
//  Copyright © 2018 Maha Moussa. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;




string SelectionFunction(string Inst_Type, string RegA, string RegB, string RegC, string Imm)
{
    string Full_Instruction;
    
    
        if (Inst_Type ==  "LW")
        {    Full_Instruction = "LW R";
           
    
            Full_Instruction += RegA + (", ") + Imm + "(R" + RegB + ')';
        }
    
    
        else
        if (Inst_Type == "SW")
        {    Full_Instruction = "SW R";
            
             
             Full_Instruction += RegA + (", ") + Imm + "(R" + RegB + ')';
        }
    
    
    
        else
            if (Inst_Type == "JMP")
        {
            Full_Instruction = "JMP " + Imm;
        }
    
    
    
        else
        if (Inst_Type == "BEQ")
        {
                Full_Instruction = "BEQ R";
        
                     
                Full_Instruction += RegA + (", R") + RegB + ", " + Imm;
        }
    
    
    
    
    
        else
        if (Inst_Type == "JALR")
        {
            Full_Instruction = "JALR R";
            
            
                
            Full_Instruction += RegA + (", R") +  RegB;
        }
    
    
    
        else
        if (Inst_Type == "RET")
        {
            Full_Instruction = "RET R";
                
            
                    
            Full_Instruction += RegA ;
        }
    
    
        else

        if (Inst_Type == "ADD")
        {
            
            Full_Instruction = "ADD R";
                
                
            
            Full_Instruction += RegA + ", R" + RegB  + ", R" + RegC  ;
            
        }
    
    
        else
        if (Inst_Type == "SUB")
        {
            Full_Instruction = "SUB R";
            
                        
            Full_Instruction += RegA + ", R" + RegB  + ", R" + RegC  ;
        }
    
    
    
        else
        if (Inst_Type == "ADDI")
        {
            Full_Instruction = "ADDI R";
            
            
            Full_Instruction += RegA + ", R" + RegB  + ", " + Imm  ;
        }
    
    
        else
        if (Inst_Type == "NAND")
        {
            Full_Instruction = "NAND R";
            
            
            Full_Instruction += RegA + ", R" + RegB  + ", R" + RegC  ;
        }
    
        else
        if (Inst_Type == "MUL")
        {
            Full_Instruction = "MUL R";
            
            
            Full_Instruction += RegA + ", R" + RegB  + ", R" + RegC  ;
            
        }
    
    
    
    
    return Full_Instruction;
}




int main() {
    
    unordered_map<int, string>  instkeeper;
    int selection;
    ifstream instfile;
    string fileline;
    int khara;
    
    
    
    
    cout<<endl<<"How do you want to enter the instructions?"<<endl<<"Enter 0 for a file, 1 for individual insstructions, 2 for a selection."<<endl;
    cin>>selection;
    
    
    
    if ( selection == 0) // the user selected a file
    {
        
        pair <int, string>  object; // object in memory to be entered in the vector
        int starting_address, instruction_number, Data_start, flag; // the starting address and the counter and the number after which tthe data starts and the answer of the user
        bool Data_Done = false ; // whether he finished entering the data or not.
        string Data;
        int Data_address;
        
        
        
        
        cout<<"please choose a starting address"<<endl;
        cin>>starting_address;
        instruction_number = starting_address;
        instfile.open("/Users/mennadessokey/Desktop/AUC/sem 5/ARCHI/Project2/Project_2_ARCHI/Project_2_ARCHI/PROGRAM");
        if (instfile.fail())
            cout<<" the file has failed to open";
        else {
            getline(instfile, fileline);
            object = {starting_address, fileline};
            cout<<endl;
            instkeeper.insert(object);
            cout<<endl<<object.first<<endl<<object.second;
            while(!instfile.eof())
            {
                instruction_number++;
                getline(instfile, fileline);
                
                object = {instruction_number, fileline};
                instkeeper.insert(object);
                cout<<endl<<object.first<<endl<<object.second;
                //cout<< " tthis is the file line" << fileline<<"done" <<endl;
    
            }
            khara = instruction_number;
            Data_start = instruction_number + 1; // the data will start drom the one after the instruction.
           
            while (!Data_Done)
            {
                cout<<"please enter the data and then its address"<<endl;
                cin >> Data;
                cout<<endl;
                cin>> Data_address;
                while (Data_address <= instruction_number)
                {
                    cout<<" This is an invalid address renter the address "<<endl;
                    cin>>Data_address;
                }
               
                object = {Data_address, Data};
                instkeeper.insert(object);
                cout<<endl<<"this is the address "<<object.first<<endl<<"this is the data "<<object.second<<endl;
                cout<<"do you wantt to enter more data? 0 for no and 1 for yes"<<endl;
                cin>>flag;
                if (flag == 0)
                    Data_Done = true;
                
               
            }
        }
        
        
    }
    

 
    
    else if (selection == 1) // the user selcting entering instructio individually
    {
        pair<int, string>  object; // object in memory to be entered in the vector
        int starting_address, instruction_number, Data_start, flag; // the starting address and the counter and the number after which tthe data starts and the answer of the user
        bool Data_Done = false ; // whether he finished entering the data or not.
        string Data;
        int Data_address;
        
        bool Done = false; // when the user is done the done flag will be true
        string instruction;
        int repeat;
        cout<<"please enter the starting address";
        cin>>starting_address;
         instruction_number = starting_address;
        do
        {
            //object.address = instruction_number;
            cout<<endl<<"Please enter instruction"<<endl;
            cin.ignore();
            getline ( cin ,  instruction);
            //object.item = instruction;
            object = {instruction_number, instruction};
            cout<<endl;
            instkeeper.insert(object);
            cout<<endl<<"this is the address "<<object.first<<endl<<"this is the data "<<object.second<<endl;
            cout<<endl<<"do you want to enter another instruction; 0 for no 1 for yes"<<endl;
            cin>>repeat;
            if (repeat)
            {
                Done = false;
                instruction_number++;
            }
            
            else
                Done = true;
            
            
        }while (!Done);
        
        Data_start = instruction_number + 1; // the data will start drom the one after the instruction.
        
        while (!Data_Done)
        {
            cout<<"please enter the data and then its address"<<endl;
            cin >> Data;
            cout<<endl;
            cin>> Data_address;
            while (Data_address <= instruction_number)
            {
                cout<<" This is an invalid address renter the address "<<endl;
                cin>>Data_address;
            }
            //object.address = Data_address;
            //object.item = Data;
            object = {Data_address, Data};
            instkeeper.insert(object);
            cout<<endl<<"this is the address "<<object.first<<endl<<"this is the data "<<object.second<<endl;
            cout<<"do you wantt to enter more data? 0 for no and 1 for yes"<<endl;
            cin>>flag;
            if (flag == 0)
                Data_Done = true;
            
            // Data_start++;
        }
        
    }
    
    
    
    
    
    
    
    
    else if (selection == 2) // the user selected a selection of lines
    {
        pair<int, string>  object; // object in memory to be entered in the vector
        int starting_address, instruction_number, Data_start, flag; // the starting address and the counter and the number after which tthe data starts and the answer of the user
        bool Data_Done = false ; // whether he finished entering the data or not.
        string Data;
        int Data_address;
        bool Done = false; // when the user is done the done flag will be true
        string instruction, Instruction_Sel, RegA, RegB, RegC,Imm;
        int repeat;
        cout<<"please enter the starting address";
        cin>>starting_address;
        instruction_number = starting_address;
       
        
        
        
        do
        {
            cout<<"Please enter a valid instructoin form the following: LW, SW, JMP, BEQ, JALR, RET, ADD, SUB, ADDI, NAND, MUL. Nothing else is supported. "<<endl;
            cin>>Instruction_Sel;
            
            
            while ((Instruction_Sel != "LW") &&(Instruction_Sel != "SW")&&(Instruction_Sel != "JMP")&&(Instruction_Sel != "BEQ")&&(Instruction_Sel != "JALR")&&(Instruction_Sel != "RET")&&(Instruction_Sel != "ADD")&&(Instruction_Sel != "SUB")&&(Instruction_Sel != "ADDI")&&(Instruction_Sel != "NAND")&&(Instruction_Sel != "MUL")) // start of the while that will check validty
                
            {
                cout<<"You have entered an invalid instruction type, re-enter the instruction "<<endl;
                cin>>Instruction_Sel;
                
            }
            
            
            
            
            cout<<"Please enter a valid number for the RegA, RegB, RegC, Imm, in the specfied order. if the instruction you have selected doesnt have one of the compenets enter it for 0. Please make sure to enter the values correctly other wise the whole program will not run/be simulated. "<<endl;
            cin>>RegA;
            cout<<endl;
            cin>>RegB;
            cout<<endl;
            cin>>RegC;
            cout<<endl;
            cin>>Imm;
            cout<<endl;
          
            instruction = SelectionFunction(Instruction_Sel,RegA,RegB,RegC,Imm);
            
            
            
            
            
            object = {instruction_number, instruction};
            cout<<endl;
            instkeeper.insert(object);
            cout<<endl<<"this is the address "<<object.first<<endl<<"this is the data "<<object.second<<endl;
            cout<<endl<<"do you want to enter another instruction; 0 for no 1 for yes"<<endl;
            cin>>repeat;
            if (repeat)
            {
                Done = false;
                instruction_number++;
            }
            
            else
                Done = true;
            
            
        }while (!Done);
        
        Data_start = instruction_number + 1; // the data will start drom the one after the instruction.
        
        while (!Data_Done)
        {
            cout<<"please enter the data and then its address"<<endl;
            cin >> Data;
            cout<<endl;
            cin>> Data_address;
            while (Data_address <= instruction_number)
            {
                cout<<" This is an invalid address renter the address "<<endl;
                cin>>Data_address;
            }
            
            object = {Data_address, Data};
            instkeeper.insert(object);
            cout<<endl<<"this is the address "<<object.first<<endl<<"this is the data "<<object.second<<endl;
            cout<<"do you wantt to enter more data? 0 for no and 1 for yes"<<endl;
            cin>>flag;
            if (flag == 0)
                Data_Done = true;
            
            
        }
        
    }
  
    
    
    for(int i = 0; i < khara; i++)
    {
        cout<<endl<<instkeeper[i];
    }
    instfile.close();
    return 0;
}














