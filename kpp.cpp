#include <stdio.h>
#include <vector>
using namespace std;
int i, j, time = 0, speed = 2;
bool strong = 0;
 
void meet(char now){
    //output kondisi bertemu
    if (now == '.'){
        time += speed;
    } else if (now == 'M'){
        printf("Bertemu dengan mekanik, siap membasmi rintangan\n");
        strong = 1;
        time += speed;
    } else if (now == 'E'){
        printf("Bertemu dengan electrical, kecepatan roda naik menjadi 200%\n");
        time += speed;
        speed = 1;
    } else if (now == 'P'){
        printf("Bertemu programmer handal\n");
        time += speed;
    } else if (now == 'O'){
        printf ("Bertemu dengan official, diajak ngonten bareng\n");
        time = (time + speed) * 2;
    } 
}

void move(char& now, char& titik, int& col, int& row, vector<vector<char>>& map){
    int newCol = col, newRow = row;
    
    if (titik == 'R'){
        newRow++;
    } else if (titik == 'L'){
        newRow--;
    } else if (titik == 'D') {
        newCol++;
    } else {
        newCol--;
    }

    //cek batas
    if (newCol >= 0 && newCol < map.size() && newRow >= 0 && newRow < map[0].size()){
        now = map[newCol][newRow];
        //jika bertemu X
        if (now == 'X'){
            if (strong){
                time += speed;
                col = newCol;
                row = newRow;
            } else {
                printf("Robot nabrak, silahkan diperbaiki\n");
                now = map[col][row];
            }
        } else {
            meet(now);
            col = newCol;
            row = newRow;
        }
    }
}

int main(){
    int n, m, p;
    scanf("%d %d", &n, &m);
    vector<vector<char>> map(n, vector<char>(m));

    //input vector map
    for (i = 0; i < n; ++i){
        for (j = 0; j < m; ++j){
            scanf(" %c", &map[i][j]);
        }
    }

    scanf("%d", &p);
    vector <char> gerak(p);
    
    //input vector gerak
    for (i = 0; i < p; ++i){
        scanf(" %c", &gerak[i]);
    }

    //eksekusi
    int col = 0, row = 0;
    char now = map[col][row];
    
    for (i = 0; i < p; ++i){
        move(now, gerak[i], col, row, map);
    }
    //cek kondisi akhir
    if (map[col][row] == 'F'){
        printf("Robot berhasil mencapai tujuan\n");
        time += speed;
    } else {
        printf("Robot gagal dalam mencapai tujuan :(\n");
    }
    //output durasi robot bergerak
    printf("Robot telah berjalan selama %d menit", time);

    return 0;
}