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

void move(char& now, char titik, int& row, int& col, vector<vector<char>> map){
    int newRow = row, newCol = col;
    //menentukan gerak, pindah titik
    switch (titik){
        case 'R': newCol++; break;
        case 'L': newCol--; break;
        case 'D': newRow++; break;
        case 'U': newRow--; break;
    }

    //cek batas, jika gerakan keluar map, maka waktu tidak dihitung
    if (newRow >= 0 && newRow < map.size() && newCol >= 0 && newCol < map[0].size()){
        now = map[newRow][newCol];
        //jika bertemu rintangan(X)
        if (now == 'X'){
            //robot tidak berpindah jika belum bertemu mekanik
            if (strong){
                time += speed;
                col = newCol;
                row = newRow;
            } else {
                printf("Robot nabrak, silahkan diperbaiki\n");
                now = map[row][col];
            }
        } else {
            //panggil fungsi move
            meet(now);
            col = newCol;
            row = newRow;
        }
    }
}

void start(int& row, int& col, int n, int m, vector<vector<char>> map){
    for (i = 0; i < n; ++i){
        for (j = 0; j < m; ++j){
            if (map[i][j] == 'S'){
                row = i; col = j;
            }
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

    //mencari start (jika titik start tidak selalu di pojok kiri atas)
    int row, col;
    start(row, col, n, m, map);
    char now = map[row][col];

    //perulangan gerakan
    for (i = 0; i < p; ++i){
        move(now, gerak[i], row, col, map);
    }

    //cek kondisi akhir
    if (map[row][col] == 'F'){
        printf("Robot berhasil mencapai tujuan\n");
        time += speed;
    } else {
        printf("Robot gagal dalam mencapai tujuan :(\n");
    }
    //output durasi robot bergerak
    printf("Robot telah berjalan selama %d menit", time);

    return 0;
}
