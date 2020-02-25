#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h> 
using namespace std;
struct paciente
{
	char dni[9];
	char nombre[50];
	char apellidos[50];
	char sexo;
	int dia,mes,anio;
	char f[80];
	char direcion[50];
	char telefonoCell[10];
	int condicion;
	int TICK=5;
	
};
struct doctor
{
	char nombreDoc[50];
	char apellidosDoc[50];
	char especialidad[50];
	bool disponible=true;
	paciente pas;
};
struct hospital
{
	char nombre[20]="HOSPITAL LAZARTE";
	char direccionH[50]="AV.NAZARET MZ.18 LT 4 N�123";
	doctor doc;
};
struct nodo
{
	hospital info;
	nodo *sgte;
};
typedef nodo *pnodo;
struct cola
{
	pnodo primero;
	pnodo ultimo;
	
};
//cola
void inicializa(cola &c);
void imprime(cola C);
void encolaPrioridad(cola &C,hospital h);
hospital desencolar(cola &C);
void insertaAlFinal(pnodo &p, hospital h);
//listas
int busca(pnodo p,hospital );
void ingresoDatos(pnodo &p,hospital &,cola &);
// hospital
void modificar(hospital & , pnodo ,cola );
void eliminar(hospital ,cola, pnodo);
void buscar(hospital );

//aicionalss
bool bisiesto(int anio,int mes,int  dia);
void menu();
void retorno_de_opc(pnodo &,hospital ,cola &);
void fecha_ingreso(hospital &h)
{
	time_t rawtime;
	time ( &rawtime );
	strcpy(h.doc.pas.f,ctime(&rawtime));
}
bool Validar_numeros(char *buffer, int tam) 
{ 
	int retval; 
	for(int i=0; i<tam && buffer[i] != 0; i++) 
	{ 
		if(buffer[i] < '0' || buffer[i] > '9'){ 
			retval=false; 
			break; 
		} 
	}	
	return retval; 
} 
//int ran(int rand)
//{
//	int time_sleep;
//	time_sleep=1000*rand;
//	for(int i=rand;i<1;i--)
//	{
//		cout<<i;
//		sleep(time_sleep);
//	}
//	return 
//}
//bool time_espera()
//{
//	if(rand==0)
//		return true;
//	else	
//		return false;
//		
//		
//}
bool ValidarLetras(char *buffer, int tam)
{ 
	int retval; 
	
	for(int i=0; i<tam && buffer[i] != 0; i++) 
	{ 
		if((buffer[i] < 'a' || buffer[i] > 'z') && (buffer[i] < 'A' || buffer[i] > 'Z') && buffer[i]!=' '){ 
			retval=false; 
			break; 
		} 
	}	
	return retval; 
} 
int busca(pnodo p,char nombre[50])
{
	if(p!=NULL)
		if(strcmp(p->info.doc.nombreDoc,nombre)==0)
			return (p->info.doc.pas.TICK);
		else
			return busca(p->sgte,nombre);
	else
			return 5;
		
}
bool verifica_Disponibilidad( pnodo p,char nombre[50])
{
	if(busca(p,nombre) <= 0)
		return false;
	else
		return true;
}

int main(int argc, char *argv[]) {
	system( "color cf");
	cola C;
	pnodo p=NULL;
	hospital h;
	inicializa(C);
	retorno_de_opc(p,h,C);
	return 0;
}
void inicializa(cola &c)
{ 
	c.primero=NULL;
	c.ultimo=NULL;
}
void menu(hospital h)
{
	cout<<"\n     ++++ "<<h.nombre<<" ++++\t\t\t\t\t\t\t "<<h.direccionH;
	cout<<"\n\n\n\t\t\t\t******************** MENU PRINCIPAL ********************";
	cout<<"\n\n\n\t\t[1] NUEVO REGISTRO ";
	cout<<"\n\n\n\t\t[2] MODIFICAR DATOS ";
	cout<<"\n\n\n\t\t[3] ELIMNAR HISTORIAL ";
	cout<<"\n\n\n\t\t[4] BUSCAR Y MOSTRAR DATOS ";
	cout<<"\n\n\n\t\t[5] LISTA DE ATENCION  ";
	cout<<"\n\n\n\t\t[6] SALIR";
	cout<<"\n\n\n\t\t\tELIJA UNA OPCION: ";
	
}
void retorno_de_opc(pnodo &p,hospital h,cola &C){
	int error = 0,op;
	do{
		fflush(stdin);
		system("cls");
		menu(h);
		if(error > 0)cout<<"(valores admitidos del 1 al 6)->";
		scanf("%d",&op);
		error++;
	} while(op	<	1	||	op	>	6);
	switch(op)
	{
		case 1:
			system("cls");
			ingresoDatos(p,h,C);
			system("pause");
			break;
		case 2:
			system("cls");
			modificar(h,p,C);
			system("pause");
			break;
		case 3:
			
			system("cls");
			eliminar(h,C,p);
			system("pause");
			break;
		case 4:
			system("cls");
			system("pause");
			break;
		case 5:
			system("cls");
			imprime(C);
			system("pause");
			break;
		case 6:
			system("cls");
			exit(1);
			system("pause");
			break;
	}
}
void ingresoDatos(pnodo &p,hospital &h,cola &C)
{
	int cuenta_caracter;
	fstream archivo;
	string dni,ale="00";
	string b=".dat";
	cout<<"\n     ++++ "<<h.nombre<<" ++++\t\t\t\t\t\t\t "<<h.direccionH;
	cout<<"\n\n\n\t\t\t\t******************** INGRESANDO DATOS ********************"<<endl;
	cout<<"\n\n\t\t--------- DATOS PERSONALES DEL PACIENTE ---------"<<endl;
	char DNI[9];
	do
	{
		cout<<"\n\t\tDNI: ";
		fflush(stdin);	
		cin>>dni;
		strcpy(DNI,dni.c_str());
		cuenta_caracter=strlen(DNI);
	}
	while(Validar_numeros(DNI,cuenta_caracter)==false	||	cuenta_caracter!=8);
	string c= dni +b;
	fstream verfarchiv;
	verfarchiv.open (c.c_str(),ios :: in | ios::binary );
	if(!verfarchiv.fail()){
		cout<<"\n\t\tYa existe un registro con el mismo DNI"<<endl;
		verfarchiv.close();
		cout<<"\n\n\n";
		system("pause");
		retorno_de_opc(p,h,C);
	}
	else{
		fstream archivo;
		archivo.open(c.c_str(),ios::out| ios::binary);
		{
			if(archivo.fail())
			{
				cout<<"NO SE PUDO CREAR O ABRIR EL ARCHIVO";	
				cout<<"\n\n\n";
				system("pause");
				retorno_de_opc(p,h,C);	
			}
			strcpy(h.doc.pas.dni,DNI);
			do{
				cout<<"\t\tNOMBRE: ";
				fflush(stdin);	
				cin.getline(h.doc.pas.nombre,50);
			} while(ValidarLetras(h.doc.pas.nombre,50)==false || strlen(h.doc.pas.nombre)<2);
			do{
				cout<<"\t\tAPELLIDOS: ";
				fflush(stdin);	
				cin.getline(h.doc.pas.apellidos,50);
			} while(ValidarLetras(h.doc.pas.apellidos,50)==false || strlen(h.doc.pas.apellidos)<2);
			do{
				cout<<"\t\tSEXO(F/M): ";
				cin>>h.doc.pas.sexo;
			} while(h.doc.pas.sexo!='f'	&&h.doc.pas.sexo!='m' && h.doc.pas.sexo!='F' &&h.doc.pas.sexo!='M');
			cout<<"\t\tFECHA DE NACIMIENTO ";
			do{	
				do{
					cout<<"\n\t\t\tdia: ";
					fflush(stdin);
					scanf("%d",&h.doc.pas.dia);
				} while(h.doc.pas.dia<=0||h.doc.pas.dia>31);
				do{
					cout<<"\t\t\tmes: ";
					fflush(stdin);
					scanf("%d",&h.doc.pas.mes);
				} while(h.doc.pas.mes<=0||h.doc.pas.mes>12);
				do{
					cout<<"\t\t\ta�o: ";
					fflush(stdin);
					scanf("%d",&h.doc.pas.anio);
					
				} while (h.doc.pas.anio<=0	||	h.doc.pas.anio<1900);
			}while(bisiesto(h.doc.pas.anio ,h.doc.pas.mes, h.doc.pas.dia) == false);
			fflush(stdin);
			cout<<"\n\t\tDIRECCION: ";
			cin.getline(h.doc.pas.direcion,100);
			do{
				cout<<"\t\tTELEFONO FIJO(044) O CELULAR: ";
				fflush(stdin);
				cin>>h.doc.pas.telefonoCell;
			} while(Validar_numeros(h.doc.pas.telefonoCell,9)==false || strlen(h.doc.pas.telefonoCell)!=9 );
			do{
				fflush(stdin);
				cout<<"\t\tCONDICION (PRIORIDAD): "<<endl;
				cout<<"\t\t\t1.-RESUCITACION"<<endl;
				cout<<"\t\t\t2.-EMERGENCIA"<<endl;
				cout<<"\t\t\t3.-URGENCIA"<<endl;
				cout<<"\t\t\t4.-URGENCIA MENOR"<<endl;
				cout<<"\t\t\t5.-SIN URGENCIA"<<endl;
				cout<<"\t\t\t\tELIJA PRIORIDAD(1-5):";
				cin>>h.doc.pas.condicion;
			}while(h.doc.pas.condicion>5 || h.doc.pas.condicion<1);
			cout<<"\n\n\n";
			system("pause");
			do{
				system("cls");
				cout<<"\n\n\t\t---------DATOS DEL DOCTOR---------"<<endl;
				
				do{	
					cout<<"\t\tNOMBRE:";	
					fflush(stdin);
					cin.getline(h.doc.nombreDoc,50);
				} while(ValidarLetras(h.doc.nombreDoc,50)==false  || strlen(h.doc.nombreDoc)<2);
				do{	
					cout<<"\t\tAPELLIDOS:";	
					fflush(stdin);
					cin.getline(h.doc.apellidosDoc,50);
				} while(ValidarLetras(h.doc.apellidosDoc,50)==false  || strlen(h.doc.apellidosDoc)<2);
				do{	
					cout<<"\t\tESPECIALIDAD:";	
					fflush(stdin);
					cin.getline(h.doc.especialidad,50);
				} while(ValidarLetras(h.doc.especialidad,50)==false  || strlen(h.doc.especialidad)<6);
				h.doc.disponible=verifica_Disponibilidad(p,h.doc.nombreDoc);
				if(h.doc.disponible)
				{
					cout<<"\t\tDOCTOR DISPONIBLE ..... DATOS GUARDADOS CON EXITO ......ESPERE SU ATENCION"<<endl;
					h.doc.pas.TICK=busca(p,h.doc.nombreDoc)-1;
					encolaPrioridad(C,h);
					insertaAlFinal(p,h);	
					cout<<"\t\tFecha de ingreso del paciente : ";
					fecha_ingreso(h);
					cout<<h.doc.pas.f;
					archivo.write((char *) &h ,sizeof(h));
					
					cout<<"\n\n\n";
					system("pause");
				}
				else{
					cout<<"\t\tDOCTOR NO DISPONIBLE"<<endl;
					cout<<"\n\n\n";
					system("pause");
				}
				
			}while(h.doc.disponible!=true);
			
		}
		archivo.close();
		retorno_de_opc(p,h,C);
	}
}
void eliminar(hospital h, cola C, pnodo p)
{
	string dni;
	string b=".dat";
	cout<<"\n\n\n\n\n\n\n\n\t\t\t\tINGRESE DNI: ";
	cin>>dni;
	cin.ignore();
	string c= dni +b;
	fstream archivo;
	
	archivo.open(c.c_str(),ios :: in | ios :: binary);
	if(!archivo){
		cout<<"\n\n\n\n\t\t\t---------------->EL ARCHIVO NO EXISTE<-------------\n\n"<<endl; 
		return;
	}
	archivo.read((char *)&h, sizeof (h));
	cout<<"\n\n\n\n\t\tDATOS DEL ARCHIVO A ELIMINAR "<<endl;
	while (!archivo.eof())
	{
		cout<<"\n\t\t\t -----> DATOS DEL PACIENTE <-----"<<endl;
		cout<<"\t\t\t\tDNI-----------------> "<<h.doc.pas.dni<<endl;
		cout<<" \t\t\t\tNOMBRES-------------> "<<h.doc.pas.nombre<<endl;
		cout<<" \t\t\t\tAPELLIDOS-----------> "<<h.doc.pas.apellidos<<endl;
		cout<<" \t\t\t\tSEXO----------------> "<<h.doc.pas.sexo<<endl;
		cout<<" \t\t\t\tFECHA DE NACIMIENTO(DD/MM/AA)---> "<<h.doc.pas.dia<<"/"<<h.doc.pas.mes<<"/"<<h.doc.pas.anio<<endl;
		cout<<" \t\t\t\tDIRECCION-----------> "<<h.doc.pas.direcion<<endl;
		cout<<" \t\t\t\tTELEFONO -----------> "<<h.doc.pas.telefonoCell<<endl;
		cout<<" \t\t\t\tPRIORIDAD-----------> "<<h.doc.pas.condicion<<endl;
		cout<<"\t\t\t -----> DATOS DEL DOCTOR <-----"<<endl;
		cout<<" \t\t\t\tNOMBRES ------------> "<<h.doc.nombreDoc<<endl;
		cout<<"\t\t\t\tAPELLIDOS-----------> "<<h.doc.apellidosDoc<<endl;
		cout<<"\t\t\t\tESPECIALIDAD-------> "<<h.doc.especialidad<<endl;
		archivo.read((char *)&h,sizeof(h));
	}
	archivo.close();
	char respuesta;
	do{
		cout<<"\n\n � DESEA ELIMINAR PERMANENTEMENTE ESTE ARCHIVO ? ";
		cin>>respuesta;
		cout<<endl;
	}while(respuesta!='S' && respuesta!='N' && respuesta!='s' && respuesta!='n');
		if(respuesta=='n'||respuesta=='N')
		{
			system("pause");
			retorno_de_opc(p,h,C);
		}
		else
			{
			remove (c.c_str());
			cout<<"ELIMINACION FINALIZADA "<<endl;
		}
		system("pause");
		retorno_de_opc(p,h,C);
}

void modificar(hospital &h,pnodo p,cola C)
{
	int opc;
	string dni;
	string b=".dat";
	cout<<"\n\n\n\n\n\n\n\n\t\t\t\tINGRESE DNI: ";
	cin>>dni;
	cin.ignore();
	string c= dni +b;
	fstream archivo;
	
	archivo.open(c.c_str(),ios :: in | ios :: binary);
	if(!archivo){
		cout<<"\n\n\n\n\t\t\t---------------->EL ARCHIVO NO EXISTE<-------------\n\n"<<endl; 
		return;
	}
	archivo.read((char *)&h, sizeof (h));
	while (!archivo.eof())
	{
		cout<<"----->DATOS DEL PACIENTE<-----"<<endl;
		cout<<"1. DNI-----------------> "<<h.doc.pas.dni<<endl;
		cout<<"2. NOMBRES-------------> "<<h.doc.pas.nombre<<endl;
		cout<<"3. APELLIDOS-----------> "<<h.doc.pas.apellidos<<endl;
		cout<<"4. SEXO----------------> "<<h.doc.pas.sexo<<endl;
		cout<<"5. FECHA DE NACIMIENTO(DD/MM/AA)---> "<<h.doc.pas.dia<<"/"<<h.doc.pas.mes<<"/"<<h.doc.pas.anio<<"\n"<<endl;
		cout<<"6. DIRECCION-----------> "<<h.doc.pas.direcion<<endl;
		cout<<"7. TELEFONO -----------> "<<h.doc.pas.telefonoCell<<endl;
		cout<<"8. PRIORIDAD-----------> "<<h.doc.pas.condicion<<endl;
		cout<<"----->DATOS DEL DOCTOR<-----"<<endl;
		cout<<"9. NOMBRES ------------> "<<h.doc.nombreDoc<<endl;
		cout<<"10. APELLIDOS-----------> "<<h.doc.apellidosDoc<<endl;
		cout<<"11. ESPECIALIDAD-------> "<<h.doc.especialidad<<endl;
		archivo.read((char *)&h,sizeof(h));
	}
	archivo.close();
	cout<<"INGRESE OPCION A CAMBIAR(1-10): "<<endl;
	cin>> opc;
	cin.ignore();
	archivo.open(c.c_str(),ios:: out | ios :: binary);
	switch(opc)
	{
		case 1:
			{
				
			}
		case 2:
		{
			do{
				cout<<"\t\tNOMBRE: ";
				fflush(stdin);	
				cin.getline(h.doc.pas.nombre,50);
			} while(ValidarLetras(h.doc.pas.nombre,50)==false || strlen(h.doc.pas.nombre)<2);
			archivo.write((char *)&h,sizeof(h));
			archivo.close();
			cout<<"informacion guardada con exito";
			break;
		}
		case 3:
		{
			do{
				
				cout<<"\t\tAPELLIDOS: ";
				fflush(stdin);	
				cin.getline(h.doc.pas.apellidos,50);
			} while(ValidarLetras(h.doc.pas.apellidos,50)==false || strlen(h.doc.pas.apellidos)<2);
			archivo.write((char *)&h,sizeof(h));
			archivo.close();
			cout<<"informacion guardada con exito";
			break;
		}
		case 4:
		{
			do{
				cout<<"\t\tSEXO(F/M): ";
				cin>>h.doc.pas.sexo;
			} while(h.doc.pas.sexo!='f'	&&h.doc.pas.sexo!='m' && h.doc.pas.sexo!='F' &&h.doc.pas.sexo!='M');
			archivo.write((char *)&h,sizeof(h));
			archivo.close();
			cout<<"informacion guardada con exito";
			break;
		}
		case 5: 
		{
			cout<<"\t\tFECHA DE NACIMIENTO ";		
			do{	
				do{
					fflush(stdin);
					cout<<"\n\t\t\tdia: ";
					scanf("%d",&h.doc.pas.dia);
				} while(h.doc.pas.dia<=0||h.doc.pas.dia>31);
				do{
					fflush(stdin);
					cout<<"\t\t\tmes: ";
					scanf("%d",&h.doc.pas.mes);
				} while(h.doc.pas.mes<=0||h.doc.pas.mes>12);
				do{
					fflush(stdin);
					cout<<"\t\t\ta�o: ";
					scanf("%d",&h.doc.pas.anio);
					
				} while (h.doc.pas.anio<=0	||	h.doc.pas.anio<1900);
			}while(bisiesto(h.doc.pas.anio ,h.doc.pas.mes, h.doc.pas.dia) == false);
			archivo.write((char *)&h,sizeof(h));
			archivo.close();
			cout<<"informacion guardada con exito";
			break;
		}
		case 6:
		{
			cout<<"\n\t\tDIRECCION: ";fflush(stdin);
			cin.getline(h.doc.pas.direcion,100);
			archivo.write((char *)&h,sizeof(h));
			archivo.close();
			cout<<"informacion guardada con exito";
			break;
		}
		case 7:
		{
			do{
				fflush(stdin);
				cout<<"\t\tTELEFONO FIJO O CELULAR: ";
				cin>>h.doc.pas.telefonoCell;
			} while(Validar_numeros(h.doc.pas.telefonoCell,9)==false|| strlen(h.doc.pas.telefonoCell)!=9);
			archivo.write((char *)&h,sizeof(h));
			archivo.close();
			cout<<"informacion guardada con exito";
			break;
		}
		case 8:
		{
			do{
				cout<<"\t\tCONDICION (PRIORIDAD): "<<endl;
				cout<<"\t\t\t1.-RESUCITACION"<<endl;
				cout<<"\t\t\t2.-EMERGENCIA"<<endl;
				cout<<"\t\t\t3.-URGENCIA"<<endl;
				cout<<"\t\t\t4.-URGENCIA MENOR"<<endl;
				cout<<"\t\t\t5.-SIN URGENCIA"<<endl;
				cout<<"\t\t\t\tELIJA PRIORIDAD(1-5):";
				cin>>h.doc.pas.condicion;
			}while(h.doc.pas.condicion>5 || h.doc.pas.condicion<1);
			archivo.write((char *)&h,sizeof(h));
			archivo.close();
			cout<<"informacion guardada con exito";
			break;
		}
		cout<<"\n\n\t\t---------DATOS DEL DOCTOR---------"<<endl;
		case 9: 
		{
			
			do{	
				fflush(stdin);
				cout<<"\t\tNOMBRE:";	
				cin.getline(h.doc.nombreDoc,50);
			} while(ValidarLetras(h.doc.nombreDoc,50)==false  || strlen(h.doc.nombreDoc)<2);
			archivo.write((char *)&h,sizeof(h));
			archivo.close();
			cout<<"informacion guardada con exito";
			break;
		}
		case 10:
		{
			do{	
				fflush(stdin);
				cout<<"\t\tAPELLIDOS:";	
				cin.getline(h.doc.apellidosDoc,50);
			} while(ValidarLetras(h.doc.apellidosDoc,50)==false  || strlen(h.doc.apellidosDoc)<2);
			archivo.write((char *)&h,sizeof(h));
			archivo.close();
			cout<<"informacion guardada con exito";
			break;
		}
		case 11:
		{
			do{	
				fflush(stdin);
				cout<<"\t\tESPECIALIDAD:";	
				cin.getline(h.doc.especialidad,50);
			} while(ValidarLetras(h.doc.especialidad,50)==false  || strlen(h.doc.especialidad)<2);
			archivo.write((char *)&h,sizeof(h));
			archivo.close();
			cout<<"informacion guardada con exito";
			break;
		}
	}
//	system("pause");
	retorno_de_opc(p,h,C);
}
bool bisiesto (int anio,int mes,int  dia)
{
	bool bisiestover= false;
	bool fechavalida;
	{
		if((anio%4==0 && anio%100!=100) || anio%400==0)
			bisiestover = true;
		if(dia>0 && dia<32 && mes>0 && mes<13 && anio>0)
		{
			if( mes==1 ||  mes==3 ||  mes==5 ||  mes==7 ||  mes==8 ||  mes==10 ||  mes==12)
			{
				cout << "\t\t\tFecha valida";
				fechavalida = true;
			}
			else
			{
				if( mes==2 && dia<30 && bisiestover){
					cout << "\t\t\tFecha valida";
					fechavalida = true;}
				else if( mes==2 && dia<29 && !bisiestover){
					cout << "\t\t\tFecha valida";
					fechavalida = true;}
				else if( mes!=2 && dia<31){
					cout << "\t\t\tFecha valida";
					fechavalida = true;}
				else{
					cout << "\t\t\tFecha no valida";
					fechavalida = false;}
			}
		}
		else
		   cout << "\t\t\t\tFecha no valida"<<endl;
	}
	return fechavalida;
}
void insertaAlFinal(pnodo &p, hospital h)
{
	pnodo nuevo,q;
	nuevo= new nodo;
	nuevo->info=h;
	nuevo->sgte=NULL;
	if(p==NULL)
		p=nuevo;
	else
	{
		q=p;
		while(q->sgte!=NULL)
			q=q->sgte;
		q->sgte=nuevo;
	}
}
void encolaPrioridad(cola &c,hospital h)
{
	pnodo nuevo = new nodo;
	nuevo->info=h;
	if(c.primero==NULL)
	{
		nuevo->sgte=NULL;
		c.primero=nuevo;
		c.ultimo=nuevo;
	}
	else
	   if(h.doc.pas.condicion<c.primero->info.doc.pas.condicion)
	{
		nuevo->sgte=c.primero;
		c.primero=nuevo;
	}
	   else
	   {
		   pnodo ant=c.primero,p=c.primero->sgte;
		   while(p!=NULL && p->info.doc.pas.condicion<=h.doc.pas.condicion)
		   {
			   ant=p;
			   p=p->sgte;
		   }
		   if(p!=NULL)
		   {
			   nuevo->sgte=ant->sgte;
			   ant->sgte=nuevo;
		   }
		   else
		   {
			   nuevo->sgte=NULL;
			   ant->sgte=nuevo;
			   c.ultimo=nuevo;
		   }
	   }
}
void imprime(cola C)
{
	int i=1;
	pnodo q;
	q=C.primero;
	cout<<"NUMERO DE ATENCION"<<" || NOMBRES Y APELLIDOS DEL PACIENTE "<<"---> CONDICION DEL PCTE<--- "<<"  NOMBRE COMPLETO DEL DOCTOR "<<endl;
	while(q!=NULL)
	{
		switch(q->info.doc.pas.condicion)
		{
			case 1:
				{
					cout<<i<<" "<<q->info.doc.pas.nombre<<" "<<q->info.doc.pas.apellidos<<"---> RESUCITACION <--- "<<q->info.doc.nombreDoc<<" "<<q->info.doc.apellidosDoc<<endl;
					q=q->sgte; i++;	break;
				}
			case 2:
				{
					cout<<i<<" "<<q->info.doc.pas.nombre<<" "<<q->info.doc.pas.apellidos<<"--> EMERGENCIA <--"<<q->info.doc.nombreDoc<<" "<<q->info.doc.apellidosDoc<<endl;
						i++; q=q->sgte; break;
				}
			case 3:
				{
						cout<<i<<" "<<q->info.doc.pas.nombre<<" "<<q->info.doc.pas.apellidos<<"--> URGENCIA <---"<<q->info.doc.nombreDoc<<" "<<q->info.doc.apellidosDoc<<endl;
						q=q->sgte; i++; break;
				}
			case 4:
				{
						cout<<i<<" "<<q->info.doc.pas.nombre<<" "<<q->info.doc.pas.apellidos<<"-->URGENCIA MENOR<--- "<<q->info.doc.nombreDoc<<" "<<q->info.doc.apellidosDoc<<endl;
						q=q->sgte; i++; break;
				}
			case 5:
				{
						cout<<i<<" "<<q->info.doc.pas.nombre<<" "<<q->info.doc.pas.apellidos<<"---> SIN URGENCIA <--- "<<q->info.doc.nombreDoc<<" "<<q->info.doc.apellidosDoc<<endl;
						q=q->sgte; i++; break;
				}
		}

	}
}
