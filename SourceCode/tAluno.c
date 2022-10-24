#include "tAluno.h"

struct tAluno{
    char nome[100];
    int matricula;
    float nota[3];
};

float Media(tAluno *aluno){
    return (aluno->nota[0] + aluno->nota[1] + aluno->nota[2])/3;
}

void LeAluno(tAluno *aluno, int matricula, float nota1, float nota2, float nota3){
    aluno->matricula = matricula;
    aluno->nota[0] = nota1;
    aluno->nota[1] = nota2;
    aluno->nota[2] = nota3;
}

void ImprimirAluno(tAluno *aluno){
    printf("mat:%d n1:%.2f n2:%.2f n3:%.2f", aluno->matricula, aluno->nota[0], aluno->nota[1], aluno->nota[2]);
}

void AtualizaMelhorAluno(tAluno* aluno1, tAluno* aluno2){
    float media1, media2;
    media1 = Media(aluno1);
    media2 = Media(aluno2);
    if (media2 > media1){
        AlunoXrecebeY(aluno1, aluno2);
    }
}

void AlunoXrecebeY(tAluno *alunoX,tAluno *alunoY){
    alunoX->matricula = alunoY->matricula;
    alunoX->nota[0] = alunoY->nota[0];
    alunoX->nota[1] = alunoY->nota[1];
    alunoX->nota[2] = alunoY->nota[2];
}


tAluno* IniciaAluno(){
    tAluno *aluno = NULL;
    aluno = (tAluno*)malloc(sizeof(struct tAluno));
    return aluno;
}

void LiberaAluno(tAluno *aluno){
    free(aluno);
}