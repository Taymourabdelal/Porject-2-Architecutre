//
//
//#include <iostream>
//
//#include <fstream>
//
//#include <string>
//
//#include <vector>
//
//#include <unordered_map>
//
//#include <queue>
//
//
//
//using namespace std;
//int RAT[8];
//int Reg_File[8];
//int ROB_head=0;
//int ROB_tail=0;
//int TEMP;
//
//struct ROB_Cell{
//    
//    
//    int num = 0 ;
//    
//    string type = "empty";
//    
//    int destination = 0;
//    
//    int value = 0;
//    
//    bool ready = 0;
//    
//    bool Flag_Empty = 1; // if 1 then its empty
//    
//    
//    
//};
//void RAT_CHECK(int RAT[], int& Vj, int& Vk, int& Type, int& Qj, int& Qk)
//{
//    
//    
//    
//    
//    if (Type == 6 || Type == 7 || Type == 9 || Type == 10)
//    {
//        if (RAT[Vj] > 0 || RAT[Vj] == 0 ) // if the RAT if busy we gie it the valur of the ROB 3ashen ya3rf yastall.
//        {
//            
//            Vj = -1;
//            
//            Qj = RAT[Vj];
//        }
//        else
//        {
//            Qj = -1;
//            Vj = Vj;
//        }
//        
//        
//        if ( (RAT[Vk] > 0 || RAT[Vk] == 0 ))
//        {
//            Vk = -1;
//            Qk = RAT[Vk];
//        }
//        else
//        {
//            Qk = -1;
//            Vk = Vk;
//        }
//        
//    }
//    
//    else
//        
//        if (Type == 0 || Type == 1 || Type == 3 || Type == 8|| Type == 5 || Type == 4)
//        {
//            if (RAT[Vj] > 0 || RAT[Vj] == 0 ) // if the RAT if busy we gie it the valur of the ROB 3ashen ya3rf yastall.
//            {
//                
//                Vj = -1;
//                
//                Qj = RAT[Vj];
//            }
//            else
//            {
//                Qj = -1;
//                Vj = Vj;
//            }
//            
//            
//        }
//    
//    
//    
//    
//    
//    
//    
//    
//    
//}
//
//void parsinginstruction ( string instruction , string& type , string& rs1 , string &rs2 , string &rd)
//{
//    int loccomma;
//    int loc;
//    int remover;
//    
//    
//    loc = instruction.find(' ');
//    type = instruction.substr(0,loc);
//    
//    
//    
//    
//    
//    
//    
//    if ((type != "JALR") && (type != "RET" )&& ( type !="JMP"))
//    {
//        
//        
//        loccomma =instruction.find(',');
//        rd = instruction.substr(loc+1,loccomma-1 - loc);
//        
//        instruction[loccomma] =NULL;
//        loc = loccomma;
//        loccomma =instruction.find(',');
//        rs1 = instruction.substr(loc+2,(loccomma-1)-(loc+1));
//        
//        
//        rs2 =  instruction.substr(loccomma+2,instruction.length()-(loccomma+2));
//        
//        
//        
//        if (rd[0] == 'R')
//        {
//            rd[0] = rd[1];
//            rd[1] = NULL;
//        }
//        
//        
//        if (rs1[0] == 'R')
//        {
//            rs1[0] = rs1[1];
//            rs1[1] = NULL;
//        }
//        
//        if (rs2[0] == 'R')
//        {
//            
//            rs2[0] = rs2[1];
//            rs2[1] = NULL;
//            
//        }
//        
//    }
//    else if ( type == "JALR")
//    {
//        
//        
//        loccomma =instruction.find(',');
//        rd = instruction.substr(loc+1,loccomma-1 - (loc+1));
//        instruction[loccomma] =NULL;
//        loc = loccomma;
//        loccomma =instruction.find(',');
//        rs1 = instruction.substr(loc+2,loccomma-1 - (loc+2));
//        
//        
//        if (rd[0] == 'R')
//        {
//            rd[0] = rd[1];
//            rd[1] = NULL;
//        }
//        if (rs1[0] == 'R')
//        {
//            rs1[0] = rs1[1];
//            rs1[1] = NULL;
//        }
//    }else if( type == "RET")
//    {
//        
//        
//        rd = instruction.substr(loc+1,instruction.length() - (loc+1));
//        if (rd[0] == 'R')
//        {
//            rd[0] = rd[1];
//            rd[1] = NULL;
//        }
//    }
//    else if ( type == "JMP" )
//    {
//        rd = instruction.substr(loc+1,instruction.length() - (loc+1));
//        
//        
//        if (rd[0] == 'R')
//        {
//            rd[0] = rd[1];
//            rd[1] = NULL;
//        }
//    }
//}
//
//
//
//
//struct IFT{
//    
//    string Instruction;
//    
//    string Issued;
//    
//    string Excueted;
//    
//    string Written;
//    
//    string Committed;
//    
//};
//
//struct ReserveStation{
//    
//    
//    
//    string Op="";
//    
//    int Dest =  -1;
//    
//    int Vj= -1;   // string wala int
//    
//    int Vk= -1;  // string wala int
//    
//    int Qk= -1;
//    
//    int Qj=-1;
//    
//    int A= -1;
//    
//    bool Busy=0; // not busy or empty
//    
//    int Result = -1;
//    
//    
//    
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
//
//
//
//void EX (ReserveStation RS[], string Inst_Type)
//{
//    
//    
//    for (int i = 0; i< 15; i ++)
//    {
//        
//        
//        if (RS[i].Busy == 1 && RS[i].Op == Inst_Type)
//        {
//            if (Inst_Type ==  "LW") // done
//            {
//                
//                if (RS[i].Qj < 0)
//                {
//                    RS[i].A = RS[i].A + RS[i].Vj;
//                }
//                
//            }
//            else
//                if (Inst_Type == "SW") // done
//                {
//                    
//                    if (RS[i].Qj < 0)
//                    {
//                        RS[i].A = RS[i].A + RS[i].Vj;
//                    }
//                    
//                }
//                else
//                    if (Inst_Type == "JMP") // done
//                    {
//                        //
//                        ;
//                    }
//                    else
//                        if (Inst_Type == "BEQ") // done
//                        {
//                            ;
//                        }
//                        else
//                            if (Inst_Type == "JALR") // done
//                            {
//                                ;
//                            }
//                            else
//                                if (Inst_Type == "RET") // done
//                                {
//                                    ;
//                                }
//                                else
//                                    if (Inst_Type == "ADD") // done
//                                    {
//                                        
//                                        if (RS[i].Qj < 0 && RS[i].Qk < 0 )
//                                        {
//                                            RS[i].Result = Reg_File[ RS[i].Vj ] + Reg_File[ RS[i].Vk ];
//                                            
//                                        }
//                                        
//                                    }
//                                    else
//                                        if (Inst_Type == "SUB") // done
//                                        {
//                                            if (RS[i].Qj < 0 && RS[i].Qk < 0 )
//                                            {
//                                                
//                                                RS[i].Result = Reg_File[ RS[i].Vj ] - Reg_File[ RS[i].Vk ];
//                                                
//                                            }
//                                            
//                                        }
//                                        else
//                                            if (Inst_Type == "ADDI") // done
//                                            {
//                                                if (RS[i].Qj < 0)
//                                                {
//                                                    RS[i].Result = Reg_File[ RS[i].Vj ] +  RS[i].Vk ;
//                                                }
//                                                
//                                            }
//                                            else
//                                                if (Inst_Type == "NAND") // done
//                                                {
//                                                    if (RS[i].Qj < 0 && RS[i].Qk < 0 )
//                                                    {
//                                                        RS[i].Result = !(Reg_File[ RS[i].Vj ] &  Reg_File[ RS[i].Vk ]) ;
//                                                    }
//                                                    
//                                                }
//                                                else
//                                                    if (Inst_Type == "MUL") // done
//                                                    {
//                                                        if (RS[i].Qj < 0 && RS[i].Qk < 0 )
//                                                        {
//                                                            RS[i].Result = Reg_File[ RS[i].Vj ] *   Reg_File[ RS[i].Vk ];
//                                                        }
//                                                        
//                                                    }
//            
//        }
//        
//        
//        
//        
//    }
//    
//    
//    
//    
//    
//    
//    
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//queue<string> instqueue;
//
//
//
//void Issue(ROB_Cell ROB[]  , string Inst_Type, ReserveStation RS[], int Dest, int Value, bool Ready, string Op, int Vj, int Vk, int A) // pass erthing and INST_TYPE haykon fel type bet3 ROB
//
//{
//    cout<<endl<<"DA5LT EL ISSAUE YA BENT";
//    
//    int RS_Dest;
//    int Qj, Qk;
//    bool  ROB_Flag = 0; // ROB_Flag b 1 if its empty
//    
//    int Type = -1,  ROB_NUMBER;
//    
//    if (Inst_Type ==  "LW") // done
//        Type = 0;
//    if (Inst_Type == "SW") // done
//        Type = 1;
//    if (Inst_Type == "JMP") // done
//        Type = 2;
//    if (Inst_Type == "BEQ") // done
//        Type = 3;
//    if (Inst_Type == "JALR") // done
//        Type = 4;
//    if (Inst_Type == "RET") // done
//        Type = 5;
//    if (Inst_Type == "ADD") // done
//        Type = 6;
//    if (Inst_Type == "SUB") // done
//        Type = 7;
//    if (Inst_Type == "ADDI") // done
//        Type = 8;
//    if (Inst_Type == "NAND") // done
//        Type = 9;
//    if (Inst_Type == "MUL") // done
//        Type = 10;
//    
//    
//    for (int i = 0; i < 6; i++) // loop that compares the rob and whether they are empty or not
//    {
//        // cout<<endl<<"DA5LT EL ISSAUE 3and"<<i;
//        
//        if (ROB[i].Flag_Empty == 1)
//        {
//            ROB_NUMBER = i;
//            
//            ROB_Flag = 1;
//            break;
//        }
//        
//        
//        
//    }
//    
//    
//    
//    RS_Dest = ROB_NUMBER;
//    
//    RAT_CHECK(RAT, Vj,  Vk,  Type,  Qj,  Qk);
//    
//    
//    
//    
//    if ( Type == 0)
//    {
//        
//        
//        
//        if ((RS[0].Busy == 0)&& ( ROB_Flag == 1))
//        {
//            ROB[ROB_NUMBER].num = ROB_NUMBER ;
//            ROB_tail=ROB_NUMBER;
//            ROB[ROB_NUMBER].type = Inst_Type;
//            ROB[ROB_NUMBER].destination = Dest;
//            ROB[ROB_NUMBER].value = Value;
//            ROB[ROB_NUMBER].ready = Ready;
//            ROB[ROB_NUMBER].Flag_Empty= 0;
//            
//            RS[0].Op= Op ;
//            
//            RS[0].Dest = RS_Dest;
//            
//            RS[0].Vj= Vj;   // string wala int
//            
//            RS[0].Vk= Vk;  // string wala int
//            
//            RS[0].Qk= Qk;
//            
//            RS[0].Qj= Qj;
//            
//            RS[0].A= A;
//            
//            RS[0].Busy= 1;
//            RAT[Dest] = ROB_NUMBER;
//            
//            
//        }
//        else
//            if (( RS[1].Busy == 0)&& ( ROB_Flag == 1))
//            {
//                ROB[ROB_NUMBER].num = ROB_NUMBER ;
//                
//                ROB_tail=ROB_NUMBER;
//                ROB[ROB_NUMBER].type = Inst_Type;
//                ROB[ROB_NUMBER].destination = Dest;
//                ROB[ROB_NUMBER].value = Value;
//                ROB[ROB_NUMBER].ready = Ready;
//                ROB[ROB_NUMBER].Flag_Empty= 0;
//                
//                RS[1].Op= Op ;
//                
//                RS[1].Dest = RS_Dest;
//                
//                RS[1].Vj= Vj;   // string wala int
//                
//                RS[1].Vk= Vk;  // string wala int
//                
//                RS[1].Qk= Qk;
//                
//                RS[1].Qj= Qj;
//                
//                RS[1].A= A;
//                
//                RS[1].Busy= 1;
//                RAT[Dest] = ROB_NUMBER;
//            }
//    }
//    else
//        if ( Type == 1)
//        {
//            if ((RS[2].Busy == 0)&& ( ROB_Flag == 1))
//            {
//                ROB[ROB_NUMBER].num = ROB_NUMBER ;
//                
//                ROB_tail=ROB_NUMBER;
//                ROB[ROB_NUMBER].type = Inst_Type;
//                ROB[ROB_NUMBER].destination = Dest;
//                ROB[ROB_NUMBER].value = Value;
//                ROB[ROB_NUMBER].ready = Ready;
//                ROB[ROB_NUMBER].Flag_Empty= 0;
//                
//                RS[2].Op= Op ;
//                
//                RS[2].Dest = RS_Dest;
//                
//                RS[2].Vj= Vj;   // string wala int
//                
//                RS[2].Vk= Vk;  // string wala int
//                
//                RS[2].Qk= Qk;
//                
//                RS[2].Qj= Qj;
//                
//                RS[2].A= A;
//                
//                RS[2].Busy= 1;
//                RAT[Dest] = ROB_NUMBER;
//                
//            }
//            else
//                if (( RS[3].Busy == 0)&& ( ROB_Flag == 1))
//                {
//                    ROB[ROB_NUMBER].num = ROB_NUMBER ;
//                    
//                    ROB_tail=ROB_NUMBER;
//                    ROB[ROB_NUMBER].type = Inst_Type;
//                    ROB[ROB_NUMBER].destination = Dest;
//                    ROB[ROB_NUMBER].value = Value;
//                    ROB[ROB_NUMBER].ready = Ready;
//                    ROB[ROB_NUMBER].Flag_Empty= 0;
//                    
//                    RS[3].Op= Op ;
//                    
//                    RS[3].Dest = RS_Dest;
//                    
//                    RS[3].Vj= Vj;   // string wala int
//                    
//                    RS[3].Vk= Vk;  // string wala int
//                    
//                    RS[3].Qk= Qk;
//                    
//                    RS[3].Qj= Qj;
//                    
//                    RS[3].A= A;
//                    
//                    RS[3].Busy= 1;
//                    RAT[Dest] = ROB_NUMBER;
//                }
//        }
//    if (( Type == 2) || (Type == 4) || (Type == 5))
//    {
//        if ((RS[4].Busy == 0)&& ( ROB_Flag == 1))
//        {
//            ROB[ROB_NUMBER].num = ROB_NUMBER ;
//            
//            ROB_tail=ROB_NUMBER;
//            ROB[ROB_NUMBER].type = Inst_Type;
//            ROB[ROB_NUMBER].destination = Dest;
//            ROB[ROB_NUMBER].value = Value;
//            ROB[ROB_NUMBER].ready = Ready;
//            ROB[ROB_NUMBER].Flag_Empty= 0;
//            
//            RS[4].Op= Op ;
//            
//            RS[4].Dest = RS_Dest;
//            
//            RS[4].Vj= Vj;   // string wala int
//            
//            RS[4].Vk= Vk;  // string wala int
//            
//            RS[4].Qk= Qk;
//            
//            RS[4].Qj= Qj;
//            
//            RS[4].A= A;
//            
//            RS[4].Busy= 1;
//            RAT[Dest] = ROB_NUMBER;
//            
//        }
//        else
//            if (( RS[5].Busy == 0)&& ( ROB_Flag == 1))
//            {
//                ROB[ROB_NUMBER].num = ROB_NUMBER ;
//                
//                ROB_tail=ROB_NUMBER;
//                ROB[ROB_NUMBER].type = Inst_Type;
//                ROB[ROB_NUMBER].destination = Dest;
//                ROB[ROB_NUMBER].value = Value;
//                ROB[ROB_NUMBER].ready = Ready;
//                ROB[ROB_NUMBER].Flag_Empty= 0;
//                
//                RS[5].Op= Op ;
//                
//                RS[5].Dest = RS_Dest;
//                
//                RS[5].Vj= Vj;   // string wala int
//                
//                RS[5].Vk= Vk;  // string wala int
//                
//                RS[5].Qk= Qk;
//                
//                RS[5].Qj= Qj;
//                
//                RS[5].A= A;
//                
//                RS[5].Busy= 1;
//                RAT[Dest] = ROB_NUMBER;
//            }
//            else
//                if (( RS[6].Busy == 0)&& ( ROB_Flag == 1))
//                {
//                    ROB[ROB_NUMBER].num = ROB_NUMBER ;
//                    
//                    ROB_tail=ROB_NUMBER;
//                    ROB[ROB_NUMBER].type = Inst_Type;
//                    ROB[ROB_NUMBER].destination = Dest;
//                    ROB[ROB_NUMBER].value = Value;
//                    ROB[ROB_NUMBER].ready = Ready;
//                    ROB[ROB_NUMBER].Flag_Empty= 0;
//                    
//                    RS[6].Op= Op ;
//                    
//                    RS[6].Dest = RS_Dest;
//                    
//                    RS[6].Vj= Vj;   // string wala int
//                    
//                    RS[6].Vk= Vk;  // string wala int
//                    
//                    RS[5].Qk= Qk;
//                    
//                    RS[6].Qj= Qj;
//                    
//                    RS[6].A= A;
//                    
//                    RS[6].Busy= 1;
//                    RAT[Dest] = ROB_NUMBER;
//                }
//    }
//    else
//        if ( Type == 3)
//        {
//            
//            if ((RS[7].Busy == 0)&& ( ROB_Flag == 1))
//            {
//                ROB[ROB_NUMBER].num = ROB_NUMBER ;
//                
//                ROB_tail=ROB_NUMBER;
//                ROB[ROB_NUMBER].type = Inst_Type;
//                ROB[ROB_NUMBER].destination = Dest;
//                ROB[ROB_NUMBER].value = Value;
//                ROB[ROB_NUMBER].ready = Ready;
//                ROB[ROB_NUMBER].Flag_Empty= 0;
//                
//                RS[7].Op= Op ;
//                
//                RS[7].Dest = RS_Dest;
//                
//                RS[7].Vj= Vj;   // string wala int
//                
//                RS[7].Vk= Vk;  // string wala int
//                
//                RS[7].Qk= Qk;
//                
//                RS[7].Qj= Qj;
//                
//                RS[7].A= A;
//                
//                RS[7].Busy= 1;
//                RAT[Dest] = ROB_NUMBER;
//                
//            }
//            else
//                if ((RS[8].Busy == 0)&& ( ROB_Flag == 1))
//                {
//                    ROB[ROB_NUMBER].num = ROB_NUMBER ;
//                    
//                    ROB_tail=ROB_NUMBER;
//                    ROB[ROB_NUMBER].type = Inst_Type;
//                    ROB[ROB_NUMBER].destination = Dest;
//                    ROB[ROB_NUMBER].value = Value;
//                    ROB[ROB_NUMBER].ready = Ready;
//                    ROB[ROB_NUMBER].Flag_Empty= 0;
//                    
//                    RS[8].Op= Op ;
//                    
//                    RS[8].Dest = RS_Dest;
//                    
//                    RS[8].Vj= Vj;   // string wala int
//                    
//                    RS[8].Vk= Vk;  // string wala int
//                    
//                    RS[8].Qk= Qk;
//                    
//                    RS[8].Qj= Qj;
//                    
//                    RS[8].A= A;
//                    
//                    RS[8].Busy= 1;
//                    RAT[Dest] = ROB_NUMBER;
//                    
//                }
//            
//        }
//        else
//            if (( Type == 6 ) || ( Type == 7)  || (Type == 8))
//            {
//                
//                if ((RS[9].Busy == 0)&& ( ROB_Flag == 1))
//                {
//                    ROB[ROB_NUMBER].num = ROB_NUMBER ;
//                    
//                    ROB_tail=ROB_NUMBER;
//                    ROB[ROB_NUMBER].type = Inst_Type;
//                    ROB[ROB_NUMBER].destination = Dest;
//                    ROB[ROB_NUMBER].value = Value;
//                    ROB[ROB_NUMBER].ready = Ready;
//                    ROB[ROB_NUMBER].Flag_Empty= 0;
//                    
//                    RS[9].Op= Op ;
//                    
//                    RS[9].Dest = RS_Dest;
//                    
//                    RS[9].Vj= Vj;   // string wala int
//                    
//                    RS[9].Vk= Vk;  // string wala int
//                    
//                    RS[9].Qk= Qk;
//                    
//                    RS[9].Qj= Qj;
//                    
//                    RS[9].A= A;
//                    
//                    RS[9].Busy= 1;
//                    RAT[Dest] = ROB_NUMBER;
//                    
//                }
//                else
//                    if ((RS[10].Busy == 0)&& ( ROB_Flag == 1))
//                    {
//                        ROB[ROB_NUMBER].num = ROB_NUMBER ;
//                        
//                        ROB_tail=ROB_NUMBER;
//                        ROB[ROB_NUMBER].type = Inst_Type;
//                        ROB[ROB_NUMBER].destination = Dest;
//                        ROB[ROB_NUMBER].value = Value;
//                        ROB[ROB_NUMBER].ready = Ready;
//                        ROB[ROB_NUMBER].Flag_Empty= 0;
//                        
//                        RS[10].Op= Op ;
//                        
//                        RS[10].Dest = RS_Dest;
//                        
//                        RS[10].Vj= Vj;   // string wala int
//                        
//                        RS[10].Vk= Vk;  // string wala int
//                        
//                        RS[10].Qk= Qk;
//                        
//                        RS[10].Qj= Qj;
//                        
//                        RS[10].A= A;
//                        
//                        RS[10].Busy= 1;
//                        RAT[Dest] = ROB_NUMBER;
//                        
//                    }
//                    else
//                        if ((RS[11].Busy == 0)&& ( ROB_Flag == 1))
//                        {
//                            ROB[ROB_NUMBER].num = ROB_NUMBER ;
//                            
//                            ROB_tail=ROB_NUMBER;
//                            ROB[ROB_NUMBER].type = Inst_Type;
//                            ROB[ROB_NUMBER].destination = Dest;
//                            ROB[ROB_NUMBER].value = Value;
//                            ROB[ROB_NUMBER].ready = Ready;
//                            ROB[ROB_NUMBER].Flag_Empty= 0;
//                            
//                            RS[11].Op= Op ;
//                            
//                            RS[11].Dest = RS_Dest;
//                            
//                            RS[11].Vj= Vj;   // string wala int
//                            
//                            RS[11].Vk= Vk;  // string wala int
//                            
//                            RS[11].Qk= Qk;
//                            
//                            RS[11].Qj= Qj;
//                            
//                            RS[11].A= A;
//                            
//                            RS[11].Busy= 1;
//                            RAT[Dest] = ROB_NUMBER;
//                            
//                        }
//                
//            }
//            else
//                if ( Type == 9)
//                {
//                    
//                    if ((RS[12].Busy == 0)&& ( ROB_Flag == 1))
//                    {
//                        ROB[ROB_NUMBER].num = ROB_NUMBER ;
//                        
//                        ROB_tail=ROB_NUMBER;
//                        ROB[ROB_NUMBER].type = Inst_Type;
//                        ROB[ROB_NUMBER].destination = Dest;
//                        ROB[ROB_NUMBER].value = Value;
//                        ROB[ROB_NUMBER].ready = Ready;
//                        ROB[ROB_NUMBER].Flag_Empty= 0;
//                        
//                        RS[12].Op= Op ;
//                        
//                        RS[12].Dest = RS_Dest;
//                        
//                        RS[12].Vj= Vj;   // string wala int
//                        
//                        RS[12].Vk= Vk;  // string wala int
//                        
//                        RS[12].Qk= Qk;
//                        
//                        RS[12].Qj= Qj;
//                        
//                        RS[12].A= A;
//                        
//                        RS[12].Busy= 1;
//                        RAT[Dest] = ROB_NUMBER;
//                        
//                    }
//                    
//                }
//                else
//                    if ( Type == 10)
//                    {
//                        
//                        if ((RS[13].Busy == 0)&& ( ROB_Flag == 1))
//                        {
//                            ROB[ROB_NUMBER].num = ROB_NUMBER ;
//                            
//                            ROB_tail=ROB_NUMBER;
//                            ROB[ROB_NUMBER].type = Inst_Type;
//                            ROB[ROB_NUMBER].destination = Dest;
//                            ROB[ROB_NUMBER].value = Value;
//                            ROB[ROB_NUMBER].ready = Ready;
//                            ROB[ROB_NUMBER].Flag_Empty= 0;
//                            
//                            RS[13].Op= Op ;
//                            
//                            RS[13].Dest = RS_Dest;
//                            
//                            RS[13].Vj= Vj;   // string wala int
//                            
//                            RS[13].Vk= Vk;  // string wala int
//                            
//                            RS[13].Qk= Qk;
//                            
//                            RS[13].Qj= Qj;
//                            
//                            RS[13].A= A;
//                            
//                            RS[13].Busy= 1;
//                            
//                        }
//                        else
//                            if ((RS[14].Busy == 0)&& ( ROB_Flag == 1))
//                            {
//                                ROB[ROB_NUMBER].num = ROB_NUMBER ;
//                                
//                                ROB_tail=ROB_NUMBER;
//                                ROB[ROB_NUMBER].type = Inst_Type;
//                                ROB[ROB_NUMBER].destination = Dest;
//                                ROB[ROB_NUMBER].value = Value;
//                                ROB[ROB_NUMBER].ready = Ready;
//                                ROB[ROB_NUMBER].Flag_Empty= 0;
//                                
//                                RS[14].Op= Op ;
//                                
//                                RS[14].Dest = RS_Dest;
//                                
//                                RS[14].Vj= Vj;   // string wala int
//                                
//                                RS[14].Vk= Vk;  // string wala int
//                                
//                                RS[14].Qk= Qk;
//                                
//                                RS[14].Qj= Qj;
//                                
//                                RS[14].A= A;
//                                
//                                RS[14].Busy= 1;
//                                
//                            }
//                        
//                        
//                    }
//    
//    
//}
//
//string SelectionFunction(string Inst_Type, string RegA, string RegB, string RegC, string Imm)
//{
//    
//    string Full_Instruction;
//    
//    
//    
//    
//    
//    if (Inst_Type ==  "LW")
//        
//    {
//        Full_Instruction = "LW R";
//        Full_Instruction += RegA + (", ") + Imm + "(R" + RegB + ')';
//        
//    }
//    
//    
//    
//    else
//        
//        if (Inst_Type == "SW")
//            
//        {
//            Full_Instruction = "SW R";
//            Full_Instruction += RegA + (", ") + Imm + "(R" + RegB + ')';
//            
//        }
//    
//        else
//            
//            if (Inst_Type == "JMP")
//                
//            {
//                
//                Full_Instruction = "JMP " + Imm;
//                
//            }
//    
//    
//            else
//                
//                if (Inst_Type == "BEQ")
//                    
//                {
//                    
//                    Full_Instruction = "BEQ R";
//                    
//                    Full_Instruction += RegA + (", R") + RegB + ", " + Imm;
//                    
//                }
//    
//                else
//                    
//                    if (Inst_Type == "JALR")
//                        
//                    {
//                        
//                        Full_Instruction = "JALR R";
//                        Full_Instruction += RegA + (", R") +  RegB;
//                        
//                    }
//    
//                    else
//                        
//                        if (Inst_Type == "RET")
//                            
//                        {
//                            
//                            Full_Instruction = "RET R";
//                            Full_Instruction += RegA ;
//                            
//                        }
//    
//                        else
//                            
//                            if (Inst_Type == "ADD")
//                                
//                            {
//                                Full_Instruction = "ADD R";
//                                
//                                Full_Instruction += RegA + ", R" + RegB  + ", R" + RegC  ;
//                                
//                            }
//                            else
//                                if (Inst_Type == "SUB")
//                                    
//                                {
//                                    Full_Instruction = "SUB R";
//                                    Full_Instruction += RegA + ", R" + RegB  + ", R" + RegC  ;
//                                }
//                                else
//                                    
//                                    if (Inst_Type == "ADDI")
//                                        
//                                    {
//                                        
//                                        Full_Instruction = "ADDI R";
//                                        Full_Instruction += RegA + ", R" + RegB  + ", " + Imm  ;
//                                        
//                                    }
//    
//                                    else
//                                        
//                                        if (Inst_Type == "NAND")
//                                            
//                                        {
//                                            
//                                            Full_Instruction = "NAND R";
//                                            Full_Instruction += RegA + ", R" + RegB  + ", R" + RegC  ;
//                                            
//                                        }
//                                        else
//                                            
//                                            if (Inst_Type == "MUL")
//                                                
//                                            {
//                                                
//                                                Full_Instruction = "MUL R";
//                                                Full_Instruction += RegA + ", R" + RegB  + ", R" + RegC  ;
//                                                
//                                                
//                                            }
//    
//    
//    return Full_Instruction;
//    
//}
//
//
//
//
//
//
//
//
//
//int main()
//{
//    
//    
//    ReserveStation RS[15];
//    vector<IFT> Info_Table;
//    string type;
//    string rs1 ;
//    string rs2 ;
//    string rd;
//    unordered_map<int, string>  instkeeper;
//    int selection;
//    ifstream instfile;
//    string fileline;
//    int starting_address;
//    string temp;
//    int IQ_Count;
//    bool issued;
//    string cur_inst;
//    pair <int, string>  object; // object in memory to be entered in the vector
//    ROB_Cell ROB[6];
//    int  instruction_number;
//    string RD, RS1, RS2, INSTRUCTION_TYPE;
//    
//    
//    
//    for (int i = 0; i < 8; i++)
//    {
//        RAT[i] = -1;
//    }
//    
//    for (int i = 0; i < 8; i++)
//    {
//        Reg_File[i] = 3;
//    }
//    
//    
//    
//    cout<<endl<<"How do you want to enter the instructions?"<<endl<<"Enter 0 for a file, 1 for individual insstructions, 2 for a selection."<<endl;
//    
//    cin>>selection;
//    
//    
//    
//    
//    
//    
//    
//    if ( selection == 0) // the user selected a file
//        
//    {
//        
//        
//        
//        int   Data_start, flag; // the starting address and the counter and the number after which tthe data starts and the answer of the user
//        
//        bool Data_Done = false ; // whether he finished entering the data or not.
//        
//        string Data;
//        
//        int Data_address;
//        
//        
//        
//        
//        
//        
//        
//        
//        
//        cout<<"please choose a starting address"<<endl;
//        
//        cin>>starting_address;
//        
//        instruction_number = starting_address;
//        
//        instfile.open("/Users/mennadessokey/Desktop/AUC/sem 5/ARCHI/Project2/Project_2_ARCHI/Project_2_ARCHI/PROGRAM");
//        
//        if (instfile.fail())
//            
//            cout<<" the file has failed to open";
//        
//        else {
//            
//            getline(instfile, fileline);
//            
//            object = {starting_address, fileline};
//            
//            cout<<endl;
//            
//            instkeeper.insert(object);
//            
//            cout<<endl<<object.first<<endl<<object.second;
//            
//            while(!instfile.eof())
//                
//            {
//                
//                instruction_number++;
//                
//                getline(instfile, fileline);
//                
//                
//                
//                object = {instruction_number, fileline};
//                
//                instkeeper.insert(object);
//                
//                cout<<endl<<object.first<<endl<<object.second;
//                
//                //cout<< " tthis is the file line" << fileline<<"done" <<endl;
//                
//                
//                
//            }
//            
//            Data_start = instruction_number + 1; // the data will start drom the one after the instruction.
//            
//            
//            
//            while (!Data_Done)
//                
//            {
//                
//                cout<<"please enter the data and then its address"<<endl;
//                
//                cin >> Data;
//                
//                cout<<endl;
//                
//                cin>> Data_address;
//                
//                while (Data_address <= instruction_number)
//                    
//                {
//                    
//                    cout<<" This is an invalid address renter the address "<<endl;
//                    
//                    cin>>Data_address;
//                    
//                }
//                
//                
//                
//                object = {Data_address, Data};
//                
//                instkeeper.insert(object);
//                
//                cout<<endl<<"this is the address "<<object.first<<endl<<"this is the data "<<object.second<<endl;
//                
//                cout<<"do you wantt to enter more data? 0 for no and 1 for yes"<<endl;
//                
//                cin>>flag;
//                
//                if (flag == 0)
//                    
//                    Data_Done = true;
//                
//                
//                
//                
//                
//            }
//            
//        }
//        
//        
//        
//        
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
//    
//    else if (selection == 1) // the user selcting entering instructio individually
//        
//    {
//        
//        
//        
//        int   Data_start, flag; // the starting address and the counter and the number after which tthe data starts and the answer of the user
//        
//        bool Data_Done = false ; // whether he finished entering the data or not.
//        
//        string Data;
//        
//        int Data_address;
//        
//        
//        
//        bool Done = false; // when the user is done the done flag will be true
//        
//        string instruction;
//        
//        int repeat;
//        
//        cout<<"please enter the starting address";
//        
//        cin>>starting_address;
//        
//        instruction_number = starting_address;
//        
//        do
//            
//        {
//            
//            //object.address = instruction_number;
//            
//            cout<<endl<<"Please enter instruction"<<endl;
//            
//            cin.ignore();
//            
//            getline ( cin ,  instruction);
//            
//            //object.item = instruction;
//            
//            object = {instruction_number, instruction};
//            
//            cout<<endl;
//            
//            instkeeper.insert(object);
//            
//            cout<<endl<<"this is the address "<<object.first<<endl<<"this is the data "<<object.second<<endl;
//            
//            cout<<endl<<"do you want to enter another instruction; 0 for no 1 for yes"<<endl;
//            
//            cin>>repeat;
//            
//            if (repeat)
//                
//            {
//                
//                Done = false;
//                
//                instruction_number++;
//                
//            }
//            
//            
//            
//            else
//                
//                Done = true;
//            
//            
//            
//            
//            
//        }while (!Done);
//        
//        
//        
//        Data_start = instruction_number + 1; // the data will start drom the one after the instruction.
//        
//        
//        
//        while (!Data_Done)
//            
//        {
//            
//            cout<<"please enter the data and then its address"<<endl;
//            
//            cin >> Data;
//            
//            cout<<endl;
//            
//            cin>> Data_address;
//            
//            while (Data_address <= instruction_number)
//                
//            {
//                
//                cout<<" This is an invalid address renter the address "<<endl;
//                
//                cin>>Data_address;
//                
//            }
//            
//            //object.address = Data_address;
//            
//            //object.item = Data;
//            
//            object = {Data_address, Data};
//            
//            instkeeper.insert(object);
//            
//            cout<<endl<<"this is the address "<<object.first<<endl<<"this is the data "<<object.second<<endl;
//            
//            cout<<"do you wantt to enter more data? 0 for no and 1 for yes"<<endl;
//            
//            cin>>flag;
//            
//            if (flag == 0)
//                
//                Data_Done = true;
//            
//            
//            
//            // Data_start++;
//            
//        }
//        
//        
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
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    else if (selection == 2) // the user selected a selection of lines
//        
//    {
//        
//        
//        
//        int  Data_start, flag; // the starting address and the counter and the number after which tthe data starts and the answer of the user
//        
//        bool Data_Done = false ; // whether he finished entering the data or not.
//        
//        string Data;
//        
//        int Data_address;
//        
//        bool Done = false; // when the user is done the done flag will be true
//        
//        string instruction, Instruction_Sel, RegA, RegB, RegC,Imm;
//        
//        int repeat;
//        
//        cout<<"please enter the starting address";
//        
//        cin>>starting_address;
//        
//        instruction_number = starting_address;
//        
//        
//        
//        
//        
//        
//        
//        
//        
//        do
//            
//        {
//            
//            cout<<"Please enter a valid instructoin form the following: LW, SW, JMP, BEQ, JALR, RET, ADD, SUB, ADDI, NAND, MUL. Nothing else is supported. "<<endl;
//            
//            cin>>Instruction_Sel;
//            
//            
//            
//            
//            
//            while ((Instruction_Sel != "LW") &&(Instruction_Sel != "SW")&&(Instruction_Sel != "JMP")&&(Instruction_Sel != "BEQ")&&(Instruction_Sel != "JALR")&&(Instruction_Sel != "RET")&&(Instruction_Sel != "ADD")&&(Instruction_Sel != "SUB")&&(Instruction_Sel != "ADDI")&&(Instruction_Sel != "NAND")&&(Instruction_Sel != "MUL")) // start of the while that will check validty
//                
//                
//                
//            {
//                
//                cout<<"You have entered an invalid instruction type, re-enter the instruction "<<endl;
//                
//                cin>>Instruction_Sel;
//                
//                
//                
//            }
//            
//            
//            
//            
//            
//            
//            
//            
//            
//            cout<<"Please enter a valid number for the RegA, RegB, RegC, Imm, in the specfied order. if the instruction you have selected doesnt have one of the compenets enter it for 0. Please make sure to enter the values correctly other wise the whole program will not run/be simulated. "<<endl;
//            
//            cin>>RegA;
//            
//            cout<<endl;
//            
//            cin>>RegB;
//            
//            cout<<endl;
//            
//            cin>>RegC;
//            
//            cout<<endl;
//            
//            cin>>Imm;
//            
//            cout<<endl;
//            
//            
//            
//            instruction = SelectionFunction(Instruction_Sel,RegA,RegB,RegC,Imm);
//            
//            
//            
//            
//            
//            
//            
//            
//            
//            
//            
//            object = {instruction_number, instruction};
//            
//            cout<<endl;
//            
//            instkeeper.insert(object);
//            
//            cout<<endl<<"this is the address "<<object.first<<endl<<"this is the data "<<object.second<<endl;
//            
//            cout<<endl<<"do you want to enter another instruction; 0 for no 1 for yes"<<endl;
//            
//            cin>>repeat;
//            
//            if (repeat)
//                
//            {
//                
//                Done = false;
//                
//                instruction_number++;
//                
//            }
//            
//            
//            
//            else
//                
//                Done = true;
//            
//            
//            
//            
//            
//        }while (!Done);
//        
//        
//        
//        Data_start = instruction_number + 1; // the data will start drom the one after the instruction.
//        
//        
//        
//        while (!Data_Done)
//            
//        {
//            
//            cout<<"please enter the data and then its address"<<endl;
//            
//            cin >> Data;
//            
//            cout<<endl;
//            
//            cin>> Data_address;
//            
//            while (Data_address <= instruction_number)
//                
//            {
//                
//                cout<<" This is an invalid address renter the address "<<endl;
//                
//                cin>>Data_address;
//                
//            }
//            
//            
//            
//            object = {Data_address, Data};
//            
//            instkeeper.insert(object);
//            
//            cout<<endl<<"this is the address "<<object.first<<endl<<"this is the data "<<object.second<<endl;
//            
//            cout<<"do you wantt to enter more data? 0 for no and 1 for yes"<<endl;
//            
//            cin>>flag;
//            
//            if (flag == 0)
//                
//                Data_Done = true;
//            
//            
//            
//            
//            
//        }
//        
//        
//        
//    }
//    
//    
//    
//    // HENA WE ACTUALLY START
//    
//    for (int i = starting_address; i <instruction_number; i++)
//    {
//        
//        parsinginstruction ( instkeeper[i] , INSTRUCTION_TYPE , RS1 , RS2 , RD);
//        
//        //cout<<"ANA BA3D EL PARSING GIRL"<<endl<<INSTRUCTION_TYPE<<endl<<RS1<<endl<<RS2<<endl<<RD;
//        
//        int R_S_1 = stoi(RS1);
//        int R_S_2 = stoi(RS2);
//        int R_S_3 = stoi(RD);
//        
//        Issue(ROB, INSTRUCTION_TYPE, RS , R_S_3, 0, 0, INSTRUCTION_TYPE, R_S_1, R_S_2, 0);
//        
//        
//        
//        EX (RS, INSTRUCTION_TYPE);
//        
//        //cout<<endl<<"HOBAAAA"<<endl<<RS[9].Result<<endl<<RS[10].Result<<endl<<RS[13].Result<<endl<<"this is the i "<<i<<endl;
//        
//        
//    }
//    
//    
//    //
//    //    for (int i = 0; i <6; i++)
//    //    {
//    //
//    //
//    //
//    //        cout<<"ANA HENA"<<endl<<INSTRUCTION_TYPE<<endl<<RS1<<endl<<RS2<<endl<<RD;
//    //
//    //
//    //
//    //
//    //        cout<<endl<<ROB[i].type<<endl<<ROB[i].destination<<endl<<ROB[i].value<<endl<<ROB[i].ready<<endl<<ROB[0].Flag_Empty<<endl;
//    //
//    //
//    //    }
//    //
//    //    for (int i = 0; i <15; i++)
//    //    {
//    //
//    //
//    //        cout<<endl<<"FUCK";
//    //
//    //
//    //
//    //
//    //        cout<<RS[i].Op<<endl<<RS[i].Vj<<endl<<RS[i].Vk<<endl<<RS[i].Qj<<endl<<RS[i].Qk<<endl<<RS[i].A<<endl<<RS[i].Busy<<endl<<"this is the RESULT"<<endl<<RS[i].Result<<endl;
//    //
//    //
//    //
//    //
//    //    }
//    instfile.close();
//    return 0;
//    
//}

