#!/bin/bash

# 기본 메뉴 구조 잡기
while true; do
    echo ""
    echo "----------------------------------------"
    echo "   강의실 시간 배정 관리 시스템"
    echo "----------------------------------------"
    echo "1. 시간 배정 요청 (Input)"
    echo "2. 과거 로그 검색 (Log Search)"
    echo "3. 종료 (Exit)"
    echo -n "메뉴를 선택하세요: "
    read choice

    case $choice in
        1)
            echo "기능 구현 예정입니다."
            ;;
        2)
            echo "기능 구현 예정입니다."
            ;;
        3)
            echo "프로그램을 종료합니다."
            break
            ;;
        *)
            echo "잘못된 입력입니다."
            ;;
    esac
done