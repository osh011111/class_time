// 1단계: 기본 구조 및 데이터 입력 (Input Parsing)
// 가장 먼저 데이터 구조체를 정의하고, 커맨드 라인 인자(argv)를 받아 파싱이 잘 되는지 확인하는 단계입니다.





#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;           // 팀 번호
    int start;        // 시작 시간
    int end;          // 종료 시간
    int is_accepted;  // 1단계 합격 여부
} TimeSlot;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s 1-3 4-6 …\n", argv[0]);
        return 1;
    }

    int count = argc - 1;
    TimeSlot teams[100];

    // 1. 데이터 파싱
    printf("=== 입력 데이터 확인 ===\n");
    for (int i = 0; i < count; i++) {
        teams[i].id = i + 1;
        // 문자열 파싱 (예: "1-3" -> start:1, end:3)
        sscanf(argv[i + 1], "%d-%d", &teams[i].start, &teams[i].end);
        teams[i].is_accepted = 0; 
        
        printf("Team %d: %d시 ~ %d시\n", teams[i].id, teams[i].start, teams[i].end);
    }

    return 0;
}