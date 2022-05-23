#***Bài tập lớn LTNC***
##Cài đặt
    - Mở terminal tại folder root.
    - Chạy MakeFile bằng cách ghi lệnh "mingw32-make" hoặc "mingw32-make -f MakeFile".
    - Chạy game.exe

##Về game
    -Là một tựa game bullet hell shoot-em up có lối chơi đơn giản. Nhiệm vụ của người chơi chỉ là bắn tất cả những gì xuấ hiện trên màn hình cũng như né bất cứ thứ gì bay đến mình.
##Các kĩ thuật sử dụng
    -Sử dụng thư viện đồ hoạ SDL, áp dụng các containers tiêu chuẩn như vector, map, bítet,..., cũng như sử dụng smart pointers để quản lý tài nguyên.
##Kinh nghiệm rút ra:
    -Tìm hiểu kĩ về các design partterns cũng như các khái niệm high-level game programming như sử dụng state pattern để điểu khiển trạng thái của game, cách sắp xếp game loop cũng như hàm update, cách sử dụng các decoupling patterns như Components, Type Objects trước khi implement vào trong code để tránh bị rối, không hiệu quả.
    -Chuẩn bị trước ý tưởng và tìm assets từ sớm nhằm tránh rối sau này.