#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <bitset>

// Функция для вычисления XOR двух чисел
int xorOperation(std::vector<int> &v) {
  int s=v[0];
  for(int i=1; i<v.size(); i++)
    s^=v[i];
  return s;
}

void fill(std::vector<int> &v){
  for(int i=0; i<v.size(); i++)
    v[i]=rand()%15;
}

void print(std::vector<int> &v){
  for(int i=0; i<v.size(); i++){
    for(int j=0; j<v[i]; j++){
      std::cout<<"*";
    }
    std::cout<<" ("<<v[i]<<")";
    std::cout<<"\n";
  }
  std::cout<<"\n";
}

int sum(std::vector<int> &v){
  int s=0;
  for(int i=0; i<v.size(); i++)
    s+=v[i];
  return s;
}

int index(std::string &s){
  for(int i=0;i<s.size();i++){
    if(s[i]=='1'){
      return i;
    }
  }
  return -1;
}





int correct_input(bool upper = false, int up_bound=-1, int low = 0) {
    bool not_first = false;
    int s_a = -1;
    std::string err = "Wrong number!!!\n";
    std::string tip = "Enter normal number!!!\n";
    do {
        std::string S_mode = "";
        s_a = 0; // обнуляем всё и перезаписываем
                
        if (std::cin.fail()) { // если с прошл цикла фейл, чиним
            std::cin.clear();
        }
        
        if (not_first) { // если true - уже ошиблись, можем писать
            std::cout << err;
        } else {
            not_first = true;
        }

        std::cout << tip; std::cin >> S_mode; // 1ая перем
        try {
            s_a = std::stoi(S_mode);  // если не число, улетаем
        } catch (...) {
            std::cout << "\n";
        }
    } while (std::cin.fail() || s_a <= low || (s_a > up_bound && upper));
    return s_a;
}


int main() {
    // Начальные условия - количество камней на каждой куче
    srand(0);
    int n;
    
    std::cout<<"Enter number of heaps  --  ";
    n=correct_input(false, 1,0);
    std::vector<int> game(n);
    std::cout<<"Random : 1, No Random : 2 "<<std::endl;
    int status = 1;
    status = correct_input(true, 2, 0);
    if(status==1){
      
      std::cout<<"It's going creation of heaps..."<<std::endl;
      fill(game);
    }
    else{
      for(int i=0;i<n;i++){
        
        game[i]=correct_input(false);
      }
      
    }
    print(game);
    
    

    // Цикл игры
    while (true) {
        // Печатаем состояние куч
        

        // Ход игрока
        int number, stones;
        std::cout << "Your turn - Enter heap number "<<1<<" to "<<n<<std::endl;
        number = correct_input(false, 1,0);
        if(number>n || number<1){
          std::cout<<"It is not available number! Please, enter right";
          continue;
        }
        std::cout << "Enter the number of stones you want to remove: ";
        
        
        stones = correct_input(false);
        if(stones<1){
          std::cout<<"It is not available number! Please, enter positive integers";
          continue;
        }
      
        // Обновляем состояние куч
        int flag=0;
        for (int i=0;i<n;i++){
          if(i==number-1){
            if(game[i]>=stones){
              game[i]-=stones;
            }
            else{
              std::cout<<"It is not available number!"<<std::endl;
              flag=1;
              break;
            }
            break;
          }
        }
        if(flag)
          continue;

        // Проверяем, завершилась ли игра
        
        if (sum(game)==0) {
            std::cout << "Player wins!" << std::endl;
            break;
        }

        print(game);
        // Ход бота
        int xorSum = xorOperation(game);
      
        int t = 0;
      
        if (xorSum != 0) {
            std::cout<<"Bot is thinking..."<<std::endl;
            // Ищем кучу, которую необходимо изменить
            // чтобы получить xorSum равный 0
            std::bitset<16> s=xorSum;
            std::string xor_string=s.to_string();
            for(int i=0; i<n; i++){
              std::bitset<16> el=game[i];
              std::string string_elem=el.to_string();
              if(string_elem[index(xor_string)]=='1'){
                game[i] = xorSum ^ game[i];
                break;
              }           
            }
        }
        else {
            std::cout<<"Bot is thinking..."<<xorSum<<std::endl;
            // Если xorSum равен 0, то бот случайным образом выбирает кучу
            // и удаляет из нее случайное количество камней
          
            while(1){
              int randomHeap = (rand() % n) + 1;
              int randomStones = (rand() % 5) + 1;
              if(game[randomHeap-1]<randomStones)
                continue;
              else
                game[randomHeap-1] -= randomStones;
                break;
            }
            
            
        }
        print(game);

        // Проверяем, завершилась ли игра
        if (sum(game)==0) {
            std::cout << "Bot wins!" << std::endl;
            break;
        }
        
    }

    return 0;
}
