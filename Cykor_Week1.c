/*  call_stack

    ���� �ý��ۿ����� ������ �޸𸮿� ���������, �� ���������� `int` �迭�� �̿��Ͽ� �޸𸮸� �����մϴ�.
    ������ SFP�� Return Address�� ���� ���� �޸� �ּҰ� ��������, �̹� ���������� -1�� ��ü�մϴ�.

    int call_stack[]      : ���� ������(`int ��`) �Ǵ� `-1` (��Ÿ������ ���п�)�� �����ϴ� int �迭
    char stack_info[][]   : call_stack[]�� ���� ��ġ(index)�� ���� ������ �����ϴ� ���ڿ� �迭

    ==========================call_stack ���� ��Ģ==========================
    �Ű� ���� / ���� ������ push�� ���   : int �� �״��
    Saved Frame Pointer �� push�� ���  : call_stack������ index
    ��ȯ �ּҰ��� push�� ���       : -1
    =======================================================================


    ==========================stack_info ���� ��Ģ==========================
    �Ű� ���� / ���� ������ push�� ���        : ������ ���� ����
    Saved Frame Pointer �� push�� ���  : � �Լ��� SFP����
    ��ȯ �ּҰ��� push�� ���                 : "Return Address"
    ========================================================================
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define STACK_SIZE 50 // �ִ� ���� ũ��

int     call_stack[STACK_SIZE];         // Call Stack�� �����ϴ� �迭
char    stack_info[STACK_SIZE][20];     // Call Stack ��ҿ� ���� ������ �����ϴ� �迭

/*  SP (Stack Pointer), FP (Frame Pointer)

    SP�� ���� ������ �ֻ�� �ε����� ����ŵ�ϴ�.
    ������ ������� �� SP = -1, �ϳ��� ���̸� `call_stack[0]` -> SP = 0, `call_stack[1]` -> SP = 1, ...

    FP�� ���� �Լ��� ���� ������ �������Դϴ�.
    ���� ���� �Լ� ���� �������� sfp�� ����ŵ�ϴ�.
*/
int SP = -1;
int FP = -1;
int temp[3];
int i = 0;

void func1(int arg1, int arg2, int arg3);
void func2(int arg1, int arg2);
void func3(int arg1);

/*
    ���� call_stack ��ü�� ����մϴ�.
    �ش� �Լ��� ��� ������� �������� ���� �ϼ����� ���� �����Դϴ�.
*/
void print_stack()
{
    if (SP == -1)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("====== Current Call Stack ======\n");

    for (int i = SP; i >= 0; i--)
    {
        if (call_stack[i] != -1)
            printf("%d : %s = %d", i, stack_info[i], call_stack[i]);
        else
            printf("%d : %s", i, stack_info[i]);

        if (i == SP)
            printf("    <=== [esp]\n"); //�ֻ�� ����
        else if (i == FP)
            printf("    <=== [ebp]\n"); //sfp �ڸ�
        else
            printf("\n");
    }
    printf("================================\n\n");
}

void push(char *c, int value) //���ÿ� push
{
    SP++;
    strncpy(stack_info[SP], c, 20);
    stack_info[SP][20] = '\0'; //�ι��� �߰�
    call_stack[SP] = value;
    if (strcmp(stack_info[SP], "Return Address") == 0) { //FP ����
        temp[i] = FP;
        FP = SP + 1;
        i++;
    }
}

int j;

void pop() {
    i--;
    if (i == 0) {
        SP = -1;
    }
    else {
        for (j = 0; j < temp[i] - temp[i - 1]; j++) {
            SP--;
        }
    }
    FP = temp[i];
}

//func ���δ� �����Ӱ� �߰��ص� ��������, �Ʒ��� ������ �ٲ����� ������
void func1(int arg1, int arg2, int arg3)
{
    int var_1 = 100;

    push("arg3", arg3);
    push("arg2", arg2);
    push("arg1", arg1);
    push("Return Address", -1);
    push("func1 SFP", temp[i-1]); //FP�� ����?? => return address ������ SFP ����
    push("var_1", var_1); // func1�� ���� ������ ���� (�Լ� ���ѷα� + push)
    print_stack();

    func2(11, 13);
    pop();// func2�� ���� ������ ���� (�Լ� ���ʷα� + pop)
    print_stack();
}


void func2(int arg1, int arg2)
{
    int var_2 = 200;

    push("arg2", arg2);
    push("arg1", arg1);
    push("Return Address", -1);
    push("func2 SFP", temp[i-1]);
    push("var_2", var_2); // func2�� ���� ������ ���� (�Լ� ���ѷα� + push)
    print_stack();

    func3(77);
    pop();// func3�� ���� ������ ���� (�Լ� ���ʷα� + pop)
    print_stack();
}
  

void func3(int arg1)
{
    int var_3 = 300;
    int var_4 = 400;

    push("arg1", arg1);
    push("Return Address", -1);
    push("func3 SFP", temp[i-1]);
    push("var_3", var_3);
    push("var_4", var_4);// func3�� ���� ������ ���� (�Լ� ���ѷα� + push)
    print_stack();
}


//main �Լ��� ���õ� stack frame�� �������� �ʾƵ� �˴ϴ�.
int main()
{
    func1(1, 2, 3);
    pop();// func1�� ���� ������ ���� (�Լ� ���ʷα� + pop)
    print_stack();
    return 0;
}