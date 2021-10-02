#include <iostream>
#include <string>

using namespace std;

void welcome(void);
int menu (void);
void num2hex(void);
void hex2num(void);

class Stack{
public:
    Stack() : index(7){};
    void push(char c){
        mem[index] = c;
        index--;
    };
    char pop(){
        index++;
        return mem[index];
    };
private:
    short index;
    char mem [8];
};

int main (){
    welcome();
    bool exit = false;
    int selectedOp;
    while(!exit){
        selectedOp = menu();
        switch (selectedOp){
            case 0:
                exit = true;
                break;
            case 1:
                num2hex();
                break;
            case 2:
                hex2num();
                break;
            default:
                cout << "Entrada invalida" << endl;
                break;
        }
    }
    return 0;
}

void welcome(void){
    cout << "Conversor numeros en punto flotante IEEE754 de 32 bits <=> abreviacion hexadecimal" << endl;
    cout << "Juan Ignacio Causse - 2021 - 72.03 Introduccion a la informatica" << endl;
}

int menu(){
    int selector;
    cout << endl;
    cout << "Ingresar 1 para numero en punto flotante => abreviacion hexadecimal" << endl;
    cout << "Ingresar 2 para abreviacion hexadecimal  => numero en punto flotante" << endl;
    cout << "Ingresar 0 para salir" << endl;
    cin >> selector;
    cout << endl;
    return selector;
}

void num2hex() {
    //VARIABLES
    float num;
    char* ptr = (char*)&num;
    char aux;
    Stack stack;
    bool inputError;

    //DATA INPUT
    cout << "Ingresar numero en punto flotante: ";
    do{
        cin >> num;
        inputError = cin.fail();
        cin.clear();
        cin.ignore(1000, '\n');
        if (inputError){
            cout << "Entrada invalida" << endl;
        }
    }
    while(inputError);
    #ifdef DEBUG
        cout << "Ingresado: " << num << endl;
    #endif

    //HEX GENERATION
    for (int i = 0; i < 4; i++){
        aux = (*ptr) & 0x0F;
        stack.push(aux);
        aux = ((*ptr) & 0xF0) >> 4;
        stack.push(aux);
        ptr++;
    }

    //HEX OUTPUT
    cout << "Hexadecimal abreviado: ";
    for (int i = 0; i < 8; i++){
        cout << uppercase << hex << (int)stack.pop();
    }
    cout << endl;
}

void hex2num() {
    //VARIABLES
    string hexa;
    string::iterator it;
    float num;
    char* ptr = (char*)&num;
    char aux, aux2;
    Stack stack;

    //DATA INPUT AND VERIFICATION
    cout << "Ingresar hexadecimal abreviado: ";
    cin >> hexa;
    if (hexa.size() != 8){
        cout << "Hexadecimal invalido" << endl;
        return;
    }
    for (it = hexa.begin(); it != hexa.end(); it++){
        if (!isxdigit(*it)){
            cout << "Hexadecimal invalido" << endl;
            return;
        }
        (*it) = tolower(*it);
    }

    //NUMBER GENERATION
    for (it = hexa.begin(); it != hexa.end(); it++){
        if (isdigit(*it)){
            aux = (*it) - '0';
        }
        else{
            aux = (*it) - 'a' + 10; //a = 10, b = 11... Por eso se suma 10.
        }
        stack.push(aux);
    }
    for (int i = 0; i < 4; i++){
        aux = aux2 = 0;
        aux2 = stack.pop();
        aux = stack.pop() << 4;
        (*ptr) = aux | aux2;
        ptr++;
    }

    //NUMBER OUTPUT
    cout << "Numero en punto flotante: " << num << endl;
}