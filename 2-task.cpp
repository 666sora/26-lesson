#include <iostream>
#include <map>
#include <string>
#include <vector>

class Phonebook {
    std::map<std::string, std::string> phonebook;
    std::map<std::string, std::vector<std::string>> phonebook_backward;

    public: 
        void setEntry() {
            std::string tempName, tempNumber;
            bool correct = false;

            std::cin.ignore();
            std::cout << "Input name: ";
            std::getline(std::cin, tempName);

            do {
                std::cout << "Input number: ";
                std::cin >> tempNumber;
                if (tempNumber.substr(0, 2) == "+7" && tempNumber.length() == 12) {
                    correct = true;
                }
                else correct = false;
            } while(!correct);

            phonebook[tempNumber] = tempName;
            phonebook_backward[tempName].push_back(tempNumber);
        }

        std::map<std::string, std::string> GetPhonebook() {
            return phonebook;
        }

        std::map<std::string, std::vector<std::string>> getPhonebookBackward() {
            return phonebook_backward;
        }
};

class Phone {
    Phonebook phonebook;

    public:
        void addEntry() {
            phonebook.setEntry();
        }
        void call() {
            std::string answer;
            std::cout << "Input name or phone number: ";
            std::cin >> answer;
            if (answer.substr(0, 2) == "+7") {
                std::map<std::string, std::string> tempPhoneBook = phonebook.GetPhonebook();
                std::map<std::string, std::string>::iterator itf = tempPhoneBook.find(answer);
                std::cout << "CALL" << std::endl;
                std::cout << itf->second << std::endl;
            }
            else {
                std::map<std::string, std::vector<std::string>> tempPhoneBookBackward = phonebook.getPhonebookBackward();
                std::map<std::string, std::vector<std::string>>::iterator itf = tempPhoneBookBackward.find(answer);
                int i = 0;
                for (auto it: itf->second) {
                    std::cout << answer << " have " << it << " phone number" << std::endl;
                    i++;
                }
                if (i == 1) {
                    std::cout << "CALL" << std::endl;
                    std::cout << itf->second[0] << std::endl;
                }
                else if (i > 1) {
                    int number_answer;
                    std::cout << "What number do you want to call(1-" << i << "): ";
                    std::cin >> number_answer;
                    i = 0;
                    for (auto it: itf->second) {
                        if (number_answer - 1 == i) {
                            std::cout << "CALL" << std::endl;
                            std::cout << itf->second[i] << std::endl;
                            break;
                        }
                        i++;
                    }
                }
            }
        }
        void sendMessage() {
            std::string answer;
            std::cout << "Input name or phone number: ";
            std::cin >> answer;
            if (answer.substr(0, 2) == "+7") {
                std::map<std::string, std::string> tempPhoneBook = phonebook.GetPhonebook();
                std::map<std::string, std::string>::iterator itf = tempPhoneBook.find(answer);
                std::string dummy_answer;
                std::cout << "Input message for " << itf->second << ": ";
                std::cin >> dummy_answer;
                std::cout << "Message has been sent" << std::endl;
            }
            else {
                std::map<std::string, std::vector<std::string>> tempPhoneBookBackward = phonebook.getPhonebookBackward();
                std::map<std::string, std::vector<std::string>>::iterator itf = tempPhoneBookBackward.find(answer);
                int i = 0;
                for (auto it: itf->second) {
                    std::cout << answer << " have " << it << " phone number" << std::endl;
                    i++;
                }
                if (i == 1) {
                    std::string dummy_answer;
                    std::cout << "Input message for " << itf->second[i] << ": ";
                    std::cin >> dummy_answer;
                    std::cout << "Message has been sent" << std::endl;
                }
                else if (i > 1) {
                    int number_answer;
                    std::cout << "What number do you want to call(1-" << i << "): ";
                    std::cin >> number_answer;
                    i = 0;
                    for (auto it: itf->second) {
                        if (number_answer - 1 == i) {
                            std::string dummy_answer;
                            std::cout << "Input message for " << itf->second[i] << ": ";
                            std::cin >> dummy_answer;
                            std::cout << "Message has been sent" << std::endl;
                            break;
                        }
                        i++;
                    }
                }
            }
        }

};

int main() {
    Phone phone;
    std::string answer;

    while (answer != "exit") {
        std::cout << "Input command: ";
        std::cin >> answer;

        if (answer == "add") {
            phone.addEntry();
        }
        else if (answer == "call") {
            phone.call();
        }
        else if (answer == "sms") {
            phone.sendMessage();
        }
    }
}

/*
Реализуйте программу простой симуляции работы мобильного телефона.
По мобильному телефону можно звонить и отправлять СМС. Также 
мобильный телефон содержит адресную книгу. Телефон и отдельные 
записи адресной книги должны быть реализованы с помощью классов. 
Все номера телефонов задаются в формате +7 <10 цифр>.
Пользователь взаимодействует с программой с помощью команд:
Команда add добавляет в адресную книгу новый номер телефона и 
ассоциирует его с именем контакта. Оба эти параметра команда 
получает от пользователя через стандартный ввод.
Команда call запрашивает у пользователя имя контакта или номер 
телефона, на который требуется позвонить. Сам по себе звонок 
симулируется с помощью вывода в консоль сообщения CALL с 
номером телефона, на который осуществляется вызов.
Команда sms. Запрашивает у пользователя номер телефона 
(или имя контакта), на который требуется послать сообщение. 
Само сообщение также вводится через стандартный ввод.
Команда exit — выход из программы.
*/