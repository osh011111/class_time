// 3단계: 빈 시간 활용 로직 추가 (Phase 2)
// 메인 배정이 끝난 후, time_map 배열을 이용해 남는 자투리 시간을 탈락한 팀에게 나눠주는 '하이브리드 로직'을 구현합니다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id; int start; int end; int is_accepted;
} TimeSlot;

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
    int time_map[24] = {0, }; // 시간표 배열 추가

    for (int i = 0; i < count; i++) {
        teams[i].id = i + 1;
        sscanf(argv[i + 1], "%d-%d", &teams[i].start, &teams[i].end);
        teams[i].is_accepted = 0;
    }

    qsort(teams, count, sizeof(TimeSlot), compare_1931);

    // [Phase 1] 메인 팀 확정 및 time_map 기록
    int last_end_time = 0;
    for (int i = 0; i < count; i++) {
        if (teams[i].start >= last_end_time) {
            teams[i].is_accepted = 1;
            last_end_time = teams[i].end;
            // 시간표에 기록
            for (int t = teams[i].start; t < teams[i].end; t++) time_map[t] = teams[i].id;
        }
    }

    // [Phase 2] 빈자리 채우기
    for (int i = 0; i < count; i++) {
        if (teams[i].is_accepted == 0) { // 탈락한 팀 확인
            for (int t = teams[i].start; t < teams[i].end; t++) {
                if (time_map[t] == 0) { // 빈 시간이면
                    time_map[t] = teams[i].id; // 줍줍
                }
            }
        }
    }

    // 디버깅용 단순 출력
    printf("=== 시간대별 점유 현황 (Raw) ===\n");
    for(int i=0; i<24; i++) {
        if(time_map[i] != 0) printf("%d시-%d시 : Team %d\n", i, i+1, time_map[i]);
    }

    return 0;
}