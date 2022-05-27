#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <map>
#include <fstream>

class Track {
    std::string track_name = "";
    std::tm creation_date = {};
    int track_duration = 0;

    public:
        void setTrackName(std::ifstream &track_stream) {
            track_stream >> track_name;
        }
        void setCreationDate(std::ifstream &track_stream) {
            int temp;
            track_stream >> temp;
            temp -= 1900;
            creation_date.tm_year = temp;
            track_stream >> temp;
            temp -= 1;
            creation_date.tm_mon = temp;
            track_stream >> creation_date.tm_mday;
        }
        void setTrackDuration(std::ifstream &track_stream) {
            track_stream >> track_duration;
        }
        std::string getTrackName() {
            return track_name;
        }

        std::tm getCreationDate() {
            return creation_date;
        }

        int getTrackDuration() {
            return track_duration;
        }
};

class Player {
    std::map<std::string, Track> tracks;

    std::string playerStatus = "";

    public:
        std::map<std::string, Track> getTrackList() {
            std::ifstream track_stream("tracklist.txt");
            while(!track_stream.eof()) {
                Track tempTrack;
                tempTrack.setTrackName(track_stream);
                tempTrack.setCreationDate(track_stream);
                tempTrack.setTrackDuration(track_stream);
                tracks[tempTrack.getTrackName()] = tempTrack;
            }
            track_stream.close();
            return tracks;
        }
        void playTrack(std::string answer = "") {
            if (playerStatus == "playing") {
                std::cout << "Track is playing right now" << std::endl;
                return;
            }
            if (answer == "") {
                std::cout << "Input track you want to play: ";
                std::cin >> answer;
            }

            std::map<std::string, Track>::iterator itf = tracks.find(answer);

            std::cout << answer << " is playing right now." << std::endl;
            std::tm tempTime = itf->second.getCreationDate();
            std::cout << "Track was created on " << tempTime.tm_year + 1900 << "/" 
                << tempTime.tm_mon + 1 << "/" << tempTime.tm_mday << std::endl;
            std::cout << "Track has duration: " << (itf->second.getTrackDuration()) / 60 
                << ":" << (itf->second.getTrackDuration()) % 60 << std::endl;
            playerStatus = "playing";
        }
        void pauseTrack() {
            if (playerStatus == "paused") {
                std::cout << "Track is already paused" << std::endl;
                return;
            }
            else if (playerStatus == "") {
                std::cout << "Nothing is playing right now" << std::endl;
                return;
            }
            else if (playerStatus == "playing") {
                std::cout << "Track paused" << std::endl;
                playerStatus = "paused";
            }
        }
        void nextTrack() {
            int i = 0;
            for (auto t: tracks) {
                i++;
            }
            std::srand(std::time(nullptr));
            i = std::rand() % (i + 1);
            int j = 0;
            std::string tempTrackName;
            for (auto t: tracks) {
                tempTrackName = t.first;
                if (i == j) break;
                j++;
            }
            playTrack(tempTrackName);
        }
        void stopTrack() {
            if (playerStatus == "") {
                std::cout << "Nothing is playing right now" << std::endl;
                return;
            }
            playerStatus = "";
            std::cout << "Track stopped" << std::endl;
        }
};

int main() {
    Player player;
    player.getTrackList();
    std::string answer;
    while (answer != "exit") {
        std::cout << "Input command: ";
        std::cin >> answer;
        
        if (answer == "play") player.playTrack();
        else if (answer == "pause") player.pauseTrack();
        else if (answer == "next") player.nextTrack();
        else if (answer == "stop") player.stopTrack();
    }
}

/*
С помощью классов реализуйте программу имитации работы аудиоплеера. 
В плеере находится несколько аудиозаписей, доступных для воспроизведения. 
Для них вы должны создать отдельный класс Track. Полями этого класса 
должны быть: название, дата создания (здесь вы можете использовать тип std::tm) и продолжительность записи в секундах.
Сам плеер тоже реализуйте с помощью класса. Внутри он должен содержать 
список доступных записей и нужные для логики работы плеера поля.
Пользователь взаимодействует с программой с помощью команд:
Команда play запрашивает у пользователя название записи для воспроизведения и 
начинает её воспроизведение. Воспроизведение симулируется с помощью вывода в 
консоль всей информации о записи. Если произведение какой-то записи уже начато, ничего не происходит.
Команда pause. Ставит запись на паузу, о чём выводит соответствующее сообщение 
в консоль. Если запись уже на паузе или не воспроизводится вовсе, ничего не происходит.
Команда next переходит к следующей записи для воспроизведения. Запись при этом 
выбирается случайно, как будто плеер работает в режиме shuffle.
Команда stop прекращает воспроизведение текущей записи, если таковая имеется. 
Об этом выводится сообщение в консоль. Два раза остановить воспроизведение 
невозможно, так что команда должна срабатывать только в первом случае.
Команда exit — выход из программы.
*/