// 2단계: 핵심 알고리즘 구현 (Sorting & Greedy Phase 1)
// 회의실 배정 문제의 핵심인 '빨리 끝나는 순서대로 정렬'하고, 겹치지 않게 메인 팀을 뽑는 로직을 추가합니다.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id; int start; int end; int is_accepted;
} TimeSlot;

// 정렬 기준: 끝나는 시간이 빠른 순서
int compare_1931(const void *a, const void *b) {
    TimeSlot *t1 = (TimeSlot *)a;
    TimeSlot *t2 = (TimeSlot *)b;
    if (t1->end != t2->end) return t1->end - t2->end;
    return t1->start - t2->start;
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    int count = argc - 1;
    TimeSlot teams[100];

    // 1. 파싱
    for (int i = 0; i < count; i++) {
        teams[i].id = i + 1;
        sscanf(argv[i + 1], "%d-%d", &teams[i].start, &teams[i].end);
        teams[i].is_accepted = 0;
    }

    // 2. 정렬 (Greedy 알고리즘 준비)
    qsort(teams, count, sizeof(TimeSlot), compare_1931);

    // [Phase 1] 메인 팀 확정 (Greedy)
    int last_end_time = 0;
    printf("=== Phase 1: 메인 배정 결과 ===\n");
    for (int i = 0; i < count; i++) {
        if (teams[i].start >= last_end_time) {
            teams[i].is_accepted = 1; // 합격 처리
            last_end_time = teams[i].end;
            printf("Team %d 배정됨 (%d-%d)\n", teams[i].id, teams[i].start, teams[i].end);
        }
    }
    
    return 0;
}