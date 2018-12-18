

#include <iostream>

#include <fstream>

#include <string>

#include <vector>

#include <unordered_map>

#include <queue>
using namespace std;

struct inst {
    string instruction;
    int index;
};


   inst instholder;
 int RAT[8];
int Reg_File[8];
int ROB_head=0;
int ROB_tail=0;
int TEMP;
bool writelw1 = true;
bool writelw0 = true;
bool branch = false;
int clk=0;
int commit_count=0;
int wrongpredictions = 0;
int Issue_count=0;
int queueindex;
int branchtarget = 0;
int prebranch = 0;
////added these
int instructionsexectued;
int state = 0;
int branchact;
bool branchpredict = true;
//vector <inst> instvec;


struct ROB_Cell{

    
    int num = 0 ;
    
    string type = "empty";
    
    int destination = 0;
    
    int value = 0;
    
    bool ready = 0;
    
    bool Flag_Empty = 1; // if 1 then its empty
    
    int info_table_num=0;
    
    
    
};

ROB_Cell ROB[6];

struct IFT{
    
    string Instruction;
    
    int Issued;
    
    int Excueted;
    
    int Written;
    
    int Committed;
    
};


bool predictiomethod2bit ( bool branchact)
{

    switch (state)
    {
        case 0:
        {
            if(branchpredict!= branchact)
                state = 0;
            else state = 1;
            
            return false;
            break;
            
        }
            
        case 1:
        {
            if(branchpredict!= branchact)
                state = 0;
            else state = 2;
            return false;
            break;
        }
            
            
        case  2:
        {
            if(branchpredict!= branchact)
                state = 1;
            else state = 3;
            return true;
            break;
        }
            
            
        case 3:{
            
            if(branchpredict!= branchact)
                state = 2;
            else state = 3;
            
            return true;
            break;
        }
        default:
            return false;
            
    }
}

struct ReserveStation{
    
    
    
    string Op="";
    
    int Dest =  -1;
    
    int Vj= -1;   // string wala int
    
    int Vk= -1;  // string wala int
    
    int Qk= -1;
    
    int Qj=-1;
    
    int A= -1;
    
    bool Busy=0; // not busy or empty
    
    int Result = -1;
    int latency = 0;
    
    
    
};

int stat_predict(int imm)
{
    if (imm<0)
        return 1;
    else return 0;
}

void commit(int clock, IFT info_Table[],  unordered_map<int, string> &mem, queue<string > &IQ, int &head, int rf[8], int& tail, int  RAT[])

{
    
    int  count = 0;
    
    
    for ( int k=0; k<2&&( count<=2); k++) {
        
        if (ROB[head].ready == true )
            
        {
            
            cout<<endl<<" ANA DA%LT EL COMMIT"<<endl;
            
            commit_count+=1;
            instructionsexectued+=1;
            cout << " rob head value in commit "<< ROB[head].value << endl;
           

      
            if(ROB[head].type=="BEQ")
                
            {
            
                
                
                if (branchpredict!=branchact) {
                     head=tail=0;
                     // reretrieveing the data from the memory should be done in the execution stage // do we really need the commit station data type talama we are checking mn el rob ?
                    wrongpredictions++;
                    ROB[head].Flag_Empty = 1;
                    for ( int i=0; i<4 && (IQ.size()!=0); i++)
                        
                        IQ.pop();
                    
                    for ( int i=0;i<4;i++)
                        
                        IQ.push(mem[ROB[head].value+i]);
                    for ( int i=0 ;i<8 ;i++)
                        
                        RAT[i]=-1;
                    
    
                }
   
            }

            else    if (ROB[head].type=="SW")
                
                mem[ROB[head].destination]=ROB[head].value;
            else if (ROB[head].type=="LW")
                mem[ROB[head].destination]=ROB[head].value;
            
            else
                rf[ROB[head].destination]=ROB[head].value;
            
            cout << " THIS IS DESTINATION" << rf[ROB[head].destination] <<" THIS IS VALUE" << ROB[head].value << endl;
            
            ROB[head].ready=false;

            info_Table[ROB[head].info_table_num].Committed=clock;

            count+=1;
            
            
            ROB[head].type = "empty";

            ROB[head].destination = 0;

            ROB[head].value = 0;

            ROB[head].info_table_num=0;

            head=(head+1)%6;

    
            
        
        
    }
    
    
}

}






void writeback(int clock,IFT info_Table[],  ReserveStation RS[] )

{
    
    
    
    int count=0;
    
    int number_writes=0;
    
    
    
    for ( int i=0; i<15 ;i++) // looping on the whole RS
        
    {
        
    
        
        if ((RS[i].Result!=-1) && (RS[i].Vj==-1) && (RS[i].Vk==-1)&& RS[i].Op!="SW" && RS[i].Op!="LW" ) // execution is done // if QK was used haywrite fi l awl abl el execution
            
        {
            
            
            
            ROB[ RS[i].Dest ].value = RS[i].Result;
            cout << "THIS IS ROB VALUE" <<  ROB[ RS[i].Dest ].value <<endl;
            ROB[ RS[i].Dest ].ready=true;
            
            RS[i].Busy=false;
            
            
            info_Table[ROB[RS[i].Dest].info_table_num].Written=1;
            
            
            
            for ( int j=0; j<15;j++) // writting values to any needed columns in the RS
                
            {
                
                if (RS[j].Qj == RS[i].Dest)
                    
                {
                    
                    RS[j].Vj= ROB[RS[i].Dest].destination;
                    
                    RS[j].Qj=-1;
                    
                }
                
                if (RS[j].Qk == RS[i].Dest )
                    
                {
                    
                    RS[j].Vk= ROB[RS[i].Dest].destination;
                    
                    RS[j].Qk=-1;
                    
                }
                
            }
            
        }
        
        else if ((RS[i].A!=-1) && (RS[i].Op=="SW" ) && (RS[i].Qk==-1))
            
            
            
        {
            
            count+=1;
            
            ROB[RS[i].Dest].ready=true;
            
            RS[i].Busy=false;
            
            ROB[RS[i].Dest].value=RS[i].Vk;
            
            info_Table[ROB[RS[i].Dest].info_table_num].Written=clock;
            
        }
        
        
        
        else  if ((RS[i].A!=-1) && (RS[i].Op=="LW"))
            
        {
            
            if ((writelw0 && RS[0].Vj!=-1) && ( RS[0].Vk!=-1) && (RS[0].Op=="LW"))

                
            {
                
                count+=1;
                
                ROB[RS[0].Dest].value=RS[0].Result;
                
                ROB[RS[0].Dest].ready=true;
                
                RS[0].Busy=false;
                
                info_Table[ROB[RS[0].Dest].info_table_num].Written=1;
                
                
                
            }
            
            
            
            
            
            if(writelw1 && (RS[1].Vj!=-1) && ( RS[1].Vk!=-1) && (RS[1].Op=="LW"))
                
            {
                
                count+=1;
                
                ROB[RS[1].Dest].value=RS[1].Result;
                
                ROB[RS[1].Dest].ready=true;
                
                RS[1].Busy=false;
                
                info_Table[ROB[RS[1].Dest].info_table_num].Written=1;
                
            }
            
            
            
        }
        
    }
    
}

void RAT_CHECK(int RAT[], int& Vj, int& Vk, int& Type, int& Qj, int& Qk)
{
  
    
    
    
    if (Type == 6 || Type == 7 || Type == 9 || Type == 10)
    {
        if (RAT[Vj] > 0 || RAT[Vj] == 0 ) // if the RAT if busy we gie it the valur of the ROB 3ashen ya3rf yastall.
        {
        
            Vj = -1;
        
            Qj = RAT[Vj];
        }
        else
        {
            Qj = -1;
            Vj = Vj;
        }
        
    
        if ( (RAT[Vk] > 0 || RAT[Vk] == 0 ))
        {
            Vk = -1;
            Qk = RAT[Vk];
        }
        else
        {
            Qk = -1;
            Vk = Vk;
        }
  
    }
    
    else
    
    if (Type == 0 || Type == 1 || Type == 3 || Type == 8|| Type == 5 || Type == 4)
    {
        if (RAT[Vj] > 0 || RAT[Vj] == 0 ) // if the RAT if busy we gie it the valur of the ROB 3ashen ya3rf yastall.
        {
            
            Vj = -1;
            
            Qj = RAT[Vj];
        }
        else
        {
            Qj = -1;
            Vj = Vj;
        }
        
        
    }
    
    
    
    
    
    
    
    
    
}

void parsinginstruction ( string instruction , string& type , string& rs1 , string &rs2 , string &rd)
{
    int loccomma;
    int loc;
    int remover;
    
    
    loc = instruction.find(' ');
    type = instruction.substr(0,loc);
    
    
    
    
    
    
    
    if ((type != "JALR") && (type != "RET" )&& ( type !="JMP"))
    {
        
        
        loccomma =instruction.find(',');
        rd = instruction.substr(loc+1,loccomma-1 - loc);
        
        instruction[loccomma] =NULL;
        loc = loccomma;
        loccomma =instruction.find(',');
        rs1 = instruction.substr(loc+2,(loccomma-1)-(loc+1));
        
        
        rs2 =  instruction.substr(loccomma+2,instruction.length()-(loccomma+2));

        
       if (rd[0] == ' ')
       {
           rd[0] = rd[1];
           rd[1] = rd[2];
           rd[2] = NULL;
       }
        if (rd[0] == 'R')
        {
            rd[0] = rd[1];
            rd[1] = NULL;
        }
        
        
        if (rs1[0] == 'R')
        {
            rs1[0] = rs1[1];
            rs1[1] = NULL;
        }
     
        if (rs2[0] == 'R')
        {
            
            rs2[0] = rs2[1];
            rs2[1] = NULL;
            
        }
        
    }
    else if ( type == "JALR")
    {
        
        
        loccomma =instruction.find(',');
        rd = instruction.substr(loc+2,loccomma-1 - (loc+1));
       
        instruction[loccomma] =NULL;
        loc = loccomma;
        loccomma =instruction.find(',');
        rs1 = instruction.substr(loc+2,loccomma-1 - (loc+2));
        
        
        if (rd[0] == 'R')
        {
            
            
            rd[0] = rd[1];
            rd[1] = NULL;
        }
        if (rs1[0] == 'R')
        {
            rs1[0] = rs1[1];
            rs1[1] = NULL;
        }
    }else if( type == "RET")
    {
        
        
        rd = instruction.substr(loc+1,instruction.length() - (loc+1));
        if (rd[0] == 'R')
        {
            rd[0] = rd[1];
            rd[1] = NULL;
        }
    }
    else if ( type == "JMP" )
    {
        
        rd = instruction.substr(loc+1,instruction.length() - (loc+1));
        
        
        if (rd[0] == 'R')
        {
            rd[0] = rd[1];
            rd[1] = NULL;
        }
        
    }
}
















 void EX (int clk,IFT info_table[],ReserveStation RS[], unordered_map<int, string> instkeeper, int PC)
{
    
    
    for (int i = 0; i< 15; i ++)
    {
        
        cout <<" DE KEDA "<< RS[i].Op<<endl;
        
    if (RS[i].Busy == 1 )
        {
            
            
            if (RS[i].Op ==  "LW") // done
            {
                
                writelw1 = true;
                writelw0 = true;
                if (RS[1].Busy == 1)
                {
                    if (RS[1].Qj < 0)
                    {
                        if ( RS[1].latency==1)
                        {
                            RS[1].A = RS[1].A + Reg_File[RS[1].Vj];
                            Reg_File[ROB[ RS[1].Dest ].destination] = atoi(instkeeper [RS[1].A].c_str() );
                            
                            RS[1].latency=0;
                            info_table[ROB[RS[1].Dest].info_table_num].Excueted=clk;
                            RS[1].Vj = -1;
                            RS[1].Vk = -1;
                        }
                        
                        else
                        {
                            RS[1].latency+=1;
                            writelw1 = false;
                        }
                        
                    }
                    
                    
                    for (int i =0; i<6; i++)
                    {
                        if (ROB[i].type == "SW")
                        {
                            if (RS[1].A == ROB[i].value)
                                writelw1 = false;
                            
                            
                        }
                        
                        
                    }
                }
                
                
                if (RS[0].Busy == 1)
                {
                    
                    if (RS[0].Qj < 0)
                    {
                        
                        if ( RS[0].latency==2)
                        {
                            
                            RS[0].latency=0;
                            RS[0].A = RS[0].A + Reg_File[RS[0].Vj];
                            cout << "some fuckin values" <<Reg_File[RS[0].Vj]<< " " <<RS[0].A<<" " <<RS[0].Dest << endl << ROB[ RS[0].Dest].destination << endl;
                            
                            for (int i =0; i<6; i++)
                            {
                                
                                if (ROB[i].type == "SW")
                                {
                                    
                                    
                                    if (RS[0].A == ROB[i].value)
                                        writelw0 = false;
                                    
                                }
                                
                                
                            }
                            
                            if( writelw0 != false){
                                Reg_File[ROB[ RS[0].Dest ].destination] = atoi(instkeeper [RS[0].A].c_str() );
                                
                                RS[0].Result = atoi(instkeeper [RS[0].A].c_str() );
                            }
                            
                            
                            
                            
                            RS[0].latency=0;
                            info_table[ROB[RS[0].Dest].info_table_num].Excueted=clk;
                            RS[0].Vj = 0;
                            RS[0].Vk = 0;
                        } else {
                            writelw0 = false;
                            RS[0].latency+=1;
                        }
                        
                    }
                    
                    
               
                
                            
                            
                        }
                    
                    
                    }
            
                    
            
            else
                if (RS[i].Op == "SW") // done
                {
                    
                    if (RS[i].Qj < 0)
                    {
                        if ( RS[i].latency==1)
                        {
                        RS[i].A = RS[i].A + Reg_File[RS[i].Vj];
                        instkeeper [ RS[i].A ] = Reg_File[   ROB[ RS[i].Dest ].destination      ];
                        info_table[ROB[RS[i].Dest].info_table_num].Excueted=clk;
                            RS[i].latency=0;
                            RS[i].Vj = -1;
                            RS[i].Vk = -1;
                        }
                        else RS[i].latency+=1;
                    }
                    
                }
            else
                if (RS[i].Op == "JMP") // done
                {
                
                    RS[i].Result = PC + 1 +  ROB[ RS[i].Dest ].destination  ;
                    branchtarget = PC + 1 +  ROB[ RS[i].Dest ].destination  ;
                    info_table[ROB[RS[i].Dest].info_table_num].Excueted=clk;
                    RS[i].Vj = -1;
                    RS[i].Vk = -1;
                    branch = true;
                    
                }
            else
                if (RS[i].Op == "BEQ") // done
                {
                    
                  
                    
                    if (branchpredict)
                    {
                        
                          branchtarget = PC +1+ RS[i].Vk ;
                        
                        
                        branch = true;
                        prebranch =  PC;
                    }
                    cout << " THE CLAUE IN B RS" << Reg_File[RS[i].Vj] << endl << Reg_File[RS[i].Dest] << endl;
                    if ( Reg_File[RS[i].Vj] == Reg_File[RS[i].Dest])
                    {
                        
                        RS[i].Result = 1;
                        branchact =1;
                        
                        info_table[ROB[RS[i].Dest].info_table_num].Excueted=clk;
                        RS[i].Vj = -1;
                        RS[i].Vk = -1;
                        
                        
                    }
                    else { RS[i].Result = 0;
                        RS[i].Vj = -1;
                        RS[i].Vk = -1;
                        branchact = 0;
                    }
                }
            else
                if (RS[i].Op == "JALR") // done
                {
                  //  cout<<"this it the value inside the rob "<<ROB[ RS[i].Dest ].destination;
                   Reg_File[ ROB[ RS[i].Dest ].destination ] = PC + 1;
                    
                    RS[i].Result =PC+1;
                    
                    info_table[ROB[RS[i].Dest].info_table_num].Excueted=clk;
                    branchtarget = Reg_File[RS[i].Vj];
                    RS[i].Vj = -1;
                    RS[i].Vk = -1;
                     branch = true;
                    
                }
            else
                if (RS[i].Op == "RET") // done
                {
                    RS[i].Result = Reg_File[ ROB[ RS[i].Dest ].destination ];
                      branchtarget = Reg_File[ ROB[ RS[i].Dest ].destination ] ;
                    info_table[ROB[RS[i].Dest].info_table_num].Excueted=clk;
                    RS[i].Vj = -1;
                    RS[i].Vk = -1;
                       branch = true;
                }
            else
                if (RS[i].Op == "ADD") // done
                {
                    
                  
                 
                    
                    if (RS[i].Qj < 0 && RS[i].Qk < 0 )
                    {
                      
                        if (RS[i].latency==1)
                        {
                          
                            RS[i].Result = Reg_File[ RS[i].Vj ] + Reg_File[ RS[i].Vk ];
                            cout <<"entered ADD" << RS[i].Result;
                            info_table[ROB[RS[i].Dest].info_table_num].Excueted=clk;
                            RS[i].latency=0;
                            RS[i].Vj = -1;
                            RS[i].Vk = -1;
                        }
                        else RS[i].latency+= 1;
                       
                        
                    }
                    
                }
            else
                if (RS[i].Op == "SUB") // done
                {
    
                    
                    if (RS[i].Qj < 0 && RS[i].Qk < 0 )
                    {
    
                        if (RS[i].latency==1)
                        {
                            
                          
                        RS[i].Result = Reg_File[ RS[i].Vj ] - Reg_File[ RS[i].Vk ];
                            cout<<"this is the result then vj then vk"<< RS[i].Result<<endl<<Reg_File[ RS[i].Vj ]<<endl<<Reg_File[ RS[i].Vk ]<<endl;
                        info_table[ROB[RS[i].Dest].info_table_num].Excueted=clk;
                            cout <<" subtraction result from ex is " << RS[i].Result << " i " << endl;
                            RS[i].latency = 0;
                            RS[i].Vj = -1;
                            RS[i].Vk = -1;
                            
                        }
                        
                        else {
                            RS[i].latency+=1;
                           
                        }
                        
                    }
                    
                }
            else
                if (RS[i].Op == "ADDI") // done
                {
                    
                    if (RS[i].Qj < 0)
                    {
                        if ( RS[i].latency==1)
                        {
                            
                        RS[i].Result = Reg_File[ RS[i].Vj ] +  RS[i].Vk ;
                            cout << "THIS IS ADDI" <<RS[i].Result;
                            info_table[ROB[RS[i].Dest].info_table_num].Excueted=clk;
                            RS[i].latency=0;
                            RS[i].Vj = -1;
                            RS[i].Vk = -1;
                        }
                        else RS[i].latency+=1;
                    }
                    
                }
            else
                if (RS[i].Op == "NAND") // done
                {
                    if (RS[i].Qj < 0 && RS[i].Qk < 0 )
                    {
                        RS[i].Result = !(Reg_File[ RS[i].Vj ] &  Reg_File[ RS[i].Vk ]) ;
                        info_table[ROB[RS[i].Dest].info_table_num].Excueted=clk;
                        RS[i].Vj = -1;
                        RS[i].Vk = -1;
                    }
                    
                }
            else
                if (RS[i].Op == "MUL") // done
                {
                    
                    if (RS[i].Qj < 0 && RS[i].Qk < 0 )
                    {
                        
                        cout <<"lstrncy bitchrdd"<< RS[i].latency<<endl;
                        if (RS[i].latency==7){
                        RS[i].Result = Reg_File[ RS[i].Vj ] *   Reg_File[ RS[i].Vk ];
                        info_table[ROB[RS[i].Dest].info_table_num].Excueted=clk;
                            RS[i].latency=0;
                            RS[i].Vj = -1;
                            RS[i].Vk = -1;
                        }
                        
                        else RS[i].latency+=1;
                    }
                    
                }
            
        }
        
        
        
        
    }

    
    
    
    
    
    
}



























queue<string> instqueue;



bool Issue( ROB_Cell ROB[] ,IFT info_Table[] , string Inst_Type, ReserveStation RS[], int Dest, int Value, bool Ready, string Op, int Vj, int Vk, int A, int clk) // pass erthing and INST_TYPE haykon fel type bet3 ROB

{
    
   
    bool Is_Issued = false ;
    int RS_Dest;
    int Qj, Qk;
    bool  ROB_Flag = 0; // ROB_Flag b 1 if its empty
    
    int Type = -1,  ROB_NUMBER;
    
    if (Inst_Type ==  "LW") // done
        Type = 0;
    if (Inst_Type == "SW") // done
        Type = 1;
    if (Inst_Type == "JMP") // done
        Type = 2;
    if (Inst_Type == "BEQ") // done
        Type = 3;
    if (Inst_Type == "JALR") // done
        Type = 4;
    if (Inst_Type == "RET") // done
        Type = 5;
    if (Inst_Type == "ADD") // done
        Type = 6;
    if (Inst_Type == "SUB") // done
        Type = 7;
    if (Inst_Type == "ADDI") // done
        Type = 8;
    if (Inst_Type == "NAND") // done
        Type = 9;
    if (Inst_Type == "MUL") // done
        Type = 10;
    
                                                
    for (int i = 0; i < 6; i++) // loop that compares the rob and whether they are empty or not
    {
        
        
        if (ROB[i].Flag_Empty == 1)
        {
            ROB_NUMBER = i;
            
            ROB_Flag = 1;
          //  cout <<" rob dest " << i << endl;
            break;
        }

        
        
    }
    
  
    
    RS_Dest = ROB_NUMBER;
    
   
    RAT_CHECK(RAT, Vj,  Vk,  Type,  Qj,  Qk);
    
    
    
    
        if ( Type == 0)
    {
        
        
        
        if ((RS[0].Busy == 0)&& ( ROB_Flag == 1))
        {
            
            ROB[ROB_NUMBER].num = ROB_NUMBER ;
            ROB_tail=ROB_NUMBER;
            ROB[ROB_NUMBER].type = Inst_Type;
            ROB[ROB_NUMBER].destination = Dest;
            ROB[ROB_NUMBER].value = Value;
            ROB[ROB_NUMBER].ready = Ready;
            ROB[ROB_NUMBER].Flag_Empty= 0;
            
            RS[0].Op= Op ;
            
            RS[0].Dest = RS_Dest;
            
            RS[0].Vj= Vj;   // string wala int
            
            RS[0].Vk= 0;  // string wala int
            
            RS[0].Qk= Qk;
            
            RS[0].Qj= Qj;
            
            RS[0].A= Vk;
            
            RS[0].Busy= 1;
            RAT[Dest] = ROB_NUMBER;
            
            info_Table[ROB[RS[0].Dest].info_table_num].Issued=clk;
            Issue_count+=1;
            Is_Issued = true;
            
            
        }
        else
        if (( RS[1].Busy == 0)&& ( ROB_Flag == 1))
        {
            ROB[ROB_NUMBER].num = ROB_NUMBER ;
            
            ROB_tail=ROB_NUMBER;
            ROB[ROB_NUMBER].type = Inst_Type;
            ROB[ROB_NUMBER].destination = Dest;
            ROB[ROB_NUMBER].value = Value;
            ROB[ROB_NUMBER].ready = Ready;
            ROB[ROB_NUMBER].Flag_Empty= 0;
            
            RS[1].Op= Op ;
            
            RS[1].Dest = RS_Dest;
            
            RS[1].Vj= Vj;   // string wala int
            
            RS[1].Vk= 0;  // string wala int
            
            RS[1].Qk= Qk;
            
            RS[1].Qj= Qj;
            
            RS[1].A= Vk;
            
            RS[1].Busy= 1;
            RAT[Dest] = ROB_NUMBER;
            info_Table[ROB[RS[1].Dest].info_table_num].Issued=clk;
            Issue_count+=1;
            Is_Issued = true;
        }
    }
    else
    if ( Type == 1)
    {
        if ((RS[2].Busy == 0)&& ( ROB_Flag == 1))
        {
            ROB[ROB_NUMBER].num = ROB_NUMBER ;
            
            ROB_tail=ROB_NUMBER;
            ROB[ROB_NUMBER].type = Inst_Type;
            ROB[ROB_NUMBER].destination = Dest;
            ROB[ROB_NUMBER].value = Value;
            ROB[ROB_NUMBER].ready = Ready;
            ROB[ROB_NUMBER].Flag_Empty= 0;
            
            RS[2].Op= Op ;
            
            RS[2].Dest = RS_Dest;
            
            RS[2].Vj= Vj;   // string wala int
            
            RS[2].Vk= Vk;  // string wala int
            
            RS[2].Qk= Qk;
            
            RS[2].Qj= Qj;
            
            RS[2].A= A;
            
            RS[2].Busy= 1;
            info_Table[ROB[RS[2].Dest].info_table_num].Issued=clk;
            Issue_count+=1;
            Is_Issued = true;
            
        }
        else
        if (( RS[3].Busy == 0)&& ( ROB_Flag == 1))
        {
            ROB[ROB_NUMBER].num = ROB_NUMBER ;
            
            ROB_tail=ROB_NUMBER;
            ROB[ROB_NUMBER].type = Inst_Type;
            ROB[ROB_NUMBER].destination = Dest;
            ROB[ROB_NUMBER].value = Value;
            ROB[ROB_NUMBER].ready = Ready;
            ROB[ROB_NUMBER].Flag_Empty= 0;
            
            RS[3].Op= Op ;
            
            RS[3].Dest = RS_Dest;
            
            RS[3].Vj= Vj;   // string wala int
            
            RS[3].Vk= Vk;  // string wala int
            
            RS[3].Qk= Qk;
            
            RS[3].Qj= Qj;
            
            RS[3].A= A;
            
            RS[3].Busy= 1;
            info_Table[ROB[RS[3].Dest].info_table_num].Issued=clk;
            Issue_count+=1;
            Is_Issued = true;
            
        }
    }
    if (( Type == 2) || (Type == 4) || (Type == 5))
    {
        
        if ((RS[4].Busy == 0)&& ( ROB_Flag == 1))
        {
            
            ROB[ROB_NUMBER].num = ROB_NUMBER ;
            
            ROB_tail=ROB_NUMBER;
            ROB[ROB_NUMBER].type = Inst_Type;
            ROB[ROB_NUMBER].destination = Dest;
            ROB[ROB_NUMBER].value = Value;
            ROB[ROB_NUMBER].ready = Ready;
            ROB[ROB_NUMBER].Flag_Empty= 0;
            
            RS[4].Op= Op ;
            
            RS[4].Dest = RS_Dest;
            
            RS[4].Vj= Vj;   // string wala int
            
            RS[4].Vk= Vk;  // string wala int
            
            RS[4].Qk= Qk;
            
            RS[4].Qj= Qj;
            
            RS[4].A= A;
            
            RS[4].Busy= 1;
            if (Op == "JALR")
                RAT[Dest] = ROB_NUMBER;
            info_Table[ROB[RS[4].Dest].info_table_num].Issued=clk;
            Issue_count+=1;
            Is_Issued = true;
            
        }
        else
            
        if (( RS[5].Busy == 0)&& ( ROB_Flag == 1))
        {
            ROB[ROB_NUMBER].num = ROB_NUMBER ;
            
            ROB_tail=ROB_NUMBER;
            ROB[ROB_NUMBER].type = Inst_Type;
            ROB[ROB_NUMBER].destination = Dest;
            ROB[ROB_NUMBER].value = Value;
            ROB[ROB_NUMBER].ready = Ready;
            ROB[ROB_NUMBER].Flag_Empty= 0;
            
            RS[5].Op= Op ;
            
            RS[5].Dest = RS_Dest;
            
            RS[5].Vj= Vj;   // string wala int
            
            RS[5].Vk= Vk;  // string wala int
            
            RS[5].Qk= Qk;
            
            RS[5].Qj= Qj;
            
            RS[5].A= A;
            
            RS[5].Busy= 1;
            if (Op == "JALR")
            RAT[Dest] = ROB_NUMBER;
            info_Table[ROB[RS[5].Dest].info_table_num].Issued=clk;
            Issue_count+=1;
            Is_Issued = true;
        }
        else
        if (( RS[6].Busy == 0)&& ( ROB_Flag == 1))
        {
            ROB[ROB_NUMBER].num = ROB_NUMBER ;
            
            ROB_tail=ROB_NUMBER;
            ROB[ROB_NUMBER].type = Inst_Type;
            ROB[ROB_NUMBER].destination = Dest;
            ROB[ROB_NUMBER].value = Value;
            ROB[ROB_NUMBER].ready = Ready;
            ROB[ROB_NUMBER].Flag_Empty= 0;
            
            RS[6].Op= Op ;
            
            RS[6].Dest = RS_Dest;
            
            RS[6].Vj= Vj;   // string wala int
            
            RS[6].Vk= Vk;  // string wala int
            
            RS[5].Qk= Qk;
            
            RS[6].Qj= Qj;
            
            RS[6].A= A;
            
            RS[6].Busy= 1;
            if (Op == "JALR")
            RAT[Dest] = ROB_NUMBER;
            
            info_Table[ROB[RS[6].Dest].info_table_num].Issued=clk;
            Issue_count+=1;
            Is_Issued = true;
        }
    }
    else
    if ( Type == 3)
    {
        
        if ((RS[7].Busy == 0)&& ( ROB_Flag == 1))
        {
            
            ROB[ROB_NUMBER].num = ROB_NUMBER ;
            
            ROB_tail=ROB_NUMBER;
            ROB[ROB_NUMBER].type = Inst_Type;
            ROB[ROB_NUMBER].destination = Dest;
            ROB[ROB_NUMBER].value = Value;
            ROB[ROB_NUMBER].ready = Ready;
            ROB[ROB_NUMBER].Flag_Empty= 0;
            
            RS[7].Op= Op ;
            
            RS[7].Dest = RS_Dest;
            
            RS[7].Vj= Vj;   // string wala int
            
            RS[7].Vk= Vk;  // string wala int
            
            RS[7].Qk= Qk;
            
            RS[7].Qj= Qj;
            
            RS[7].A= A;
            
            RS[7].Busy= 1;
            RAT[Dest] = ROB_NUMBER;
            
            info_Table[ROB[RS[7].Dest].info_table_num].Issued=clk;
            Issue_count+=1;
            Is_Issued = true;
            
        }
        else
        if ((RS[8].Busy == 0)&& ( ROB_Flag == 1))
        {
                ROB[ROB_NUMBER].num = ROB_NUMBER ;
            
                ROB_tail=ROB_NUMBER;
                ROB[ROB_NUMBER].type = Inst_Type;
                ROB[ROB_NUMBER].destination = Dest;
                ROB[ROB_NUMBER].value = Value;
                ROB[ROB_NUMBER].ready = Ready;
                ROB[ROB_NUMBER].Flag_Empty= 0;
                
                RS[8].Op= Op ;
                
                RS[8].Dest = RS_Dest;
                
                RS[8].Vj= Vj;   // string wala int
                
                RS[8].Vk= Vk;  // string wala int
                
                RS[8].Qk= Qk;
                
                RS[8].Qj= Qj;
                
                RS[8].A= A;
                
                RS[8].Busy= 1;
                RAT[Dest] = ROB_NUMBER;
            
            info_Table[ROB[RS[8].Dest].info_table_num].Issued=clk;
            Issue_count+=1;
            Is_Issued = true;
                
        }
        
    }
    else
    if (( Type == 6 ) || ( Type == 7)  || (Type == 8))
    {
        
            
        if ((RS[9].Busy == 0)&& ( ROB_Flag == 1))
            {
                ROB[ROB_NUMBER].num = ROB_NUMBER ;
                
                ROB_tail=ROB_NUMBER;
                ROB[ROB_NUMBER].type = Inst_Type;
                ROB[ROB_NUMBER].destination = Dest;
                ROB[ROB_NUMBER].value = Value;
                ROB[ROB_NUMBER].ready = Ready;
                ROB[ROB_NUMBER].Flag_Empty= 0;
                
                RS[9].Op= Op ;
                
                RS[9].Dest = RS_Dest;
                
                RS[9].Vj= Vj;   // string wala int
                
                RS[9].Vk= Vk;  // string wala int
                
                RS[9].Qk= Qk;
                
                RS[9].Qj= Qj;
                
                RS[9].A= A;
                
                RS[9].Busy= 1;
                RAT[Dest] = ROB_NUMBER;
                
                info_Table[ROB[RS[9].Dest].info_table_num].Issued=clk;
                Issue_count+=1;
                Is_Issued = true;
        }
        else
        if ((RS[10].Busy == 0)&& ( ROB_Flag == 1))
            {
                    ROB[ROB_NUMBER].num = ROB_NUMBER ;
                
                    ROB_tail=ROB_NUMBER;
                    ROB[ROB_NUMBER].type = Inst_Type;
                    ROB[ROB_NUMBER].destination = Dest;
                    ROB[ROB_NUMBER].value = Value;
                    ROB[ROB_NUMBER].ready = Ready;
                    ROB[ROB_NUMBER].Flag_Empty= 0;
                    
                    RS[10].Op= Op ;
                    
                    RS[10].Dest = RS_Dest;
                    
                    RS[10].Vj= Vj;   // string wala int
                    
                    RS[10].Vk= Vk;  // string wala int
                    
                    RS[10].Qk= Qk;
                    
                    RS[10].Qj= Qj;
                    
                    RS[10].A= A;
                    
                    RS[10].Busy= 1;
                    RAT[Dest] = ROB_NUMBER;
                
                info_Table[ROB[RS[10].Dest].info_table_num].Issued=clk;
                Issue_count+=1;
                Is_Issued = true;
                    
            }
        else
        if ((RS[11].Busy == 0)&& ( ROB_Flag == 1))
        {
            ROB[ROB_NUMBER].num = ROB_NUMBER ;
            
            ROB_tail=ROB_NUMBER;
            ROB[ROB_NUMBER].type = Inst_Type;
            ROB[ROB_NUMBER].destination = Dest;
            ROB[ROB_NUMBER].value = Value;
            ROB[ROB_NUMBER].ready = Ready;
            ROB[ROB_NUMBER].Flag_Empty= 0;
            
            RS[11].Op= Op ;
            
            RS[11].Dest = RS_Dest;
            
            RS[11].Vj= Vj;   // string wala int
            
            RS[11].Vk= Vk;  // string wala int
            
            RS[11].Qk= Qk;
            
            RS[11].Qj= Qj;
            
            RS[11].A= A;
            
            RS[11].Busy= 1;
            RAT[Dest] = ROB_NUMBER;
        
            info_Table[ROB[RS[11].Dest].info_table_num].Issued=clk;
            Issue_count+=1;
            Is_Issued = true;
        }
            
    }
    else
    if ( Type == 9)
    {
        
        if ((RS[12].Busy == 0)&& ( ROB_Flag == 1))
        {
            ROB[ROB_NUMBER].num = ROB_NUMBER ;
            
            ROB_tail=ROB_NUMBER;
            ROB[ROB_NUMBER].type = Inst_Type;
            ROB[ROB_NUMBER].destination = Dest;
            ROB[ROB_NUMBER].value = Value;
            ROB[ROB_NUMBER].ready = Ready;
            ROB[ROB_NUMBER].Flag_Empty= 0;
            
            RS[12].Op= Op ;
            
            RS[12].Dest = RS_Dest;
            
            RS[12].Vj= Vj;   // string wala int
            
            RS[12].Vk= Vk;  // string wala int
            
            RS[12].Qk= Qk;
            
            RS[12].Qj= Qj;
            
            RS[12].A= A;
            
            RS[12].Busy= 1;
            RAT[Dest] = ROB_NUMBER;
            
            info_Table[ROB[RS[12].Dest].info_table_num].Issued=clk;
            Issue_count+=1;
            Is_Issued = true;
            
        }
        
    }
    else
    if ( Type == 10)
    {
            
            if ((RS[13].Busy == 0)&& ( ROB_Flag == 1))
            {
                ROB[ROB_NUMBER].num = ROB_NUMBER ;
                
                ROB_tail=ROB_NUMBER;
                ROB[ROB_NUMBER].type = Inst_Type;
                ROB[ROB_NUMBER].destination = Dest;
                ROB[ROB_NUMBER].value = Value;
                ROB[ROB_NUMBER].ready = Ready;
                ROB[ROB_NUMBER].Flag_Empty= 0;
                
                RS[13].Op= Op ;
                
                RS[13].Dest = RS_Dest;
                
                RS[13].Vj= Vj;   // string wala int
                
                RS[13].Vk= Vk;  // string wala int
                
                RS[13].Qk= Qk;
                
                RS[13].Qj= Qj;
                
                RS[13].A= A;
                
                RS[13].Busy= 1;
                info_Table[ROB[RS[13].Dest].info_table_num].Issued=clk;
                Issue_count+=1;
                Is_Issued = true;
            }
        else
        if ((RS[14].Busy == 0)&& ( ROB_Flag == 1))
        {
                ROB[ROB_NUMBER].num = ROB_NUMBER ;
            
                ROB_tail=ROB_NUMBER;
                ROB[ROB_NUMBER].type = Inst_Type;
                ROB[ROB_NUMBER].destination = Dest;
                ROB[ROB_NUMBER].value = Value;
                ROB[ROB_NUMBER].ready = Ready;
                ROB[ROB_NUMBER].Flag_Empty= 0;
                
                RS[14].Op= Op ;
                
                RS[14].Dest = RS_Dest;
                
                RS[14].Vj= Vj;   // string wala int
                
                RS[14].Vk= Vk;  // string wala int
                
                RS[14].Qk= Qk;
                
                RS[14].Qj= Qj;
                
                RS[14].A= A;
                
                RS[14].Busy= 1;
            info_Table[ROB[RS[14].Dest].info_table_num].Issued=clk;
            Issue_count+=1;
            Is_Issued = true;
                
        }
        
            
    }
    return Is_Issued;
}
        
    string SelectionFunction(string Inst_Type, string RegA, string RegB, string RegC, string Imm)
    {
        
        string Full_Instruction;
        
        
        
        
        
        if (Inst_Type ==  "LW")
            
        {
            Full_Instruction = "LW R";
            Full_Instruction += RegA + (", ") + Imm + "(R" + RegB + ')';
            
        }
        
        
        
        else
            
        if (Inst_Type == "SW")
                
        {
                Full_Instruction = "SW R";
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
        
        
        
        
        
        

        
        
        int main()
{

            
    string inst;
        ReserveStation RS[15];
        IFT Info_Table[30];
        string type;
        string rs1 ;
        string rs2 ;
        string rd;
        unordered_map<int, string>  instkeeper;
 
        int selection;
        ifstream instfile;
        string fileline;
        int starting_address;
        string temp;
        int IQ_Count;
       // bool issued;
        string cur_inst;
        pair <int, string>  object; // object in memory to be entered in the vector
        int  instruction_number;
        string RD, RS1, RS2, INSTRUCTION_TYPE;
        int R_S_1, R_S_2, R_S_3;
   
    
    for (int i = 0; i < 8; i++)
    {
        RAT[i] = -1;
    }

    for (int i = 0; i < 8; i++)
    {
        Reg_File[i] = 7;
    }
  
        
        
                cout<<endl<<"How do you want to enter the instructions?"<<endl<<"Enter 0 for a file, 1 for individual insstructions, 2 for a selection."<<endl;
        
                cin>>selection;
        
        
        
    
    


                if ( selection == 0) // the user selected a file

                {



                    int   Data_start, flag; // the starting address and the counter and the number after which tthe data starts and the answer of the user

                    bool Data_Done = false ; // whether he finished entering the data or not.

                    string Data;

                    int Data_address;









                    cout<<"please choose a starting address"<<endl;

                    cin>>starting_address;

                    instruction_number = starting_address;

                    instfile.open("/Users/taymourabdelal/Documents/UniShit/Architecure/ARCHI_Project/ARCHI_Project/PROGRAM");

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



                    int   Data_start, flag; // the starting address and the counter and the number after which tthe data starts and the answer of the user

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



                    int  Data_start, flag; // the starting address and the counter and the number after which tthe data starts and the answer of the user

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
                     
                        instholder.instruction = instruction;
                        instholder.index = instruction_number;

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
    

        // HENA WE ACTUALLY START
    int i =starting_address;
    
    if (branch == false)
    queueindex=starting_address;
    else {
        
        queueindex = branchtarget;
        while(!instqueue.empty())
        {
            
            instqueue.pop();
        }
        
        branch =false;
       
       
         commit_count = 0;
        
    }
    
   

     while (commit_count < instruction_number)
     {
        // cout <<instruction_number;
  
         int insthold;
         if (branch){
             
             queueindex = branchtarget;
             
             for(int i = 0;!instqueue.empty();i++)
             {
                 string x;
                 instqueue.pop();
             }
             
             branch =false;
             commit_count = 0;
             int insthold =  1 + instruction_number - queueindex;
             while ( instqueue.size()<4 && queueindex-1<=instruction_number-1 && instkeeper[queueindex-1]!="") //what if i have more than 4 inst ater branch
             {
                 
                 instqueue.push(instkeeper[queueindex-1]);
                 cout << " this is te queue index " << queueindex <<endl;
                 cout << " this is the instruction_number " << instruction_number << endl;
                 cout << " This is the pushed instruction" << instkeeper[queueindex-1] << endl;
                 
                 queueindex++;
                 
             }
            
             Issue_count = 0;
            instruction_number =  insthold;
           
             
         }
      
         while ( instqueue.size()<4 && queueindex<=instruction_number-1 && instkeeper[queueindex]!="" &&!branch)
         {

             instqueue.push(instkeeper[queueindex]);
             cout << " this is te queue index " << queueindex <<endl;
             cout << " this is the instruction_number " << instruction_number << endl;
  
             queueindex++;
             
         }
         
         
         cout<<" this is inst keep" <<instkeeper[1];
       
         
         if (Issue_count != instruction_number )
         {
            
             inst=instqueue.front();
             cout << " this is the front of the queue " << inst << endl;
             cout <<" the issue count is " << Issue_count << endl;
            
     //   parsinginstruction ( instkeeper[i] , INSTRUCTION_TYPE , RS1 , RS2 , RD);
        if (inst != "")
        parsinginstruction ( inst , INSTRUCTION_TYPE , RS1 , RS2 , RD);

        if (RS1 == "")
             R_S_1 = -123232;
        else
            R_S_1 = stoi(RS1);


        if (RS2 == "")
             R_S_2 = -123232;
        else
            R_S_2 = stoi(RS2);

        if (RD == "")
            
             R_S_3 = -123232;
        else
            R_S_3 = stoi(RD);


       if ( Issue(ROB,Info_Table, INSTRUCTION_TYPE, RS , R_S_3, 0, 0, INSTRUCTION_TYPE, R_S_1, R_S_2, 0, clk))
           instqueue.pop();
           
         }



        EX (clk,Info_Table,RS, instkeeper, Issue_count); // changed instruction number to queue index then to issue count

         cout << " the OP " <<RS[9].Op;
         cout <<" the OP " << RS[13].Op;
         cout << " the OP " <<RS[10].Op;
         cout << " the OP " <<RS[11].Op;
         
   

        writeback(clk, Info_Table, RS);

      //  cout << " the result of subtraction " << RS[9].Result;

        commit(clk, Info_Table,  instkeeper, instqueue,  ROB_head, Reg_File, ROB_tail, RAT);
         
              //   predictiomethod2bit(branchact);

         i++;
         clk++;

       // cout << " commit count is "<< commit_count;
//
//         for ( int i=0; i<4; i++)
//             cout << i << Info_Table[i].Committed << endl;
//         cout << endl;

    }

    for (int i = 0; i<8; i++)
    {
        cout<<endl<<"this is the reg "<<endl<< Reg_File[i];
    }

    cout << " Miss predictions" << wrongpredictions <<endl;
    cout << " Total Cycles " <<clk << endl;
    cout << "Total Instrctions Executed "<< instructionsexectued;
    
        instfile.close();
                    return 0;
        
    }

