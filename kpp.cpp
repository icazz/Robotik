#include <stdio.h>
#include <vector>
using namespace std;
int i, j, time = 0, speed = 2;
bool strong = 0;

void meet(char now){
    //output kondisi bertemu
    switch (now){
        case '.':
            time += speed;
            break;
        case 'M':
            printf("Bertemu dengan mekanik, siap membasmi rintangan\n");
            strong = 1;
            time += speed;
            break;
        case 'E':
            printf("Bertemu dengan electrical, kecepatan roda naik menjadi 200%\n");
            time += speed;
            speed = 1;
            break;
        case 'P':
            printf("Bertemu programmer handal\n");
            time += speed;
            break;
        case 'O':
            printf ("Bertemu dengan official, diajak ngonten bareng\n");
            time = (time + speed) * 2;
            break;
    } 
}

void move(char& now, char titik, int& col, int& row, vector<vector<char>> map){
    int newCol = col, newRow = row;
    //menentukan gerak, pindah titik
    switch (titik){
        case 'R': newRow++; break;
        case 'L': newRow--; break;
        case 'D': newCol++; break;
        case 'U': newCol--; break;
    }

    //cek batas, jika gerakan keluar map, maka waktu tidak dihitung
    if (newCol >= 0 && newCol < map.size() && newRow >= 0 && newRow < map[0].size()){
        now = map[newCol][newRow];
        //jika bertemu rintangan(X)
        if (now == 'X'){
            //robot tidak berpindah jika belum bertemu mekanik
            if (strong){
                time += speed;
                col = newCol;
                row = newRow;
            } else {
                printf("Robot nabrak, silahkan diperbaiki\n");
                now = map[col][row];
            }
        } else {
            //panggil fungsi move
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

    //menentukan titik start
    int col = 0, row = 0;
    char now = map[col][row];
    //perulangan gerakan
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
