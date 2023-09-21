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
  for(int i=0; i<v.size(); i++)
    std::cout<<v[i]<<" ";
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


int main() {
    // Начальные условия - количество камней на каждой куче
    srand(0);
    int n;
    
    std::cout<<"Введите число куч  --  ";
    std::cin>>n;
    std::vector<int> game(n);
    std::cout<<"Рандомно : 1, Не рандомно : 2 "<<std::endl;
    int status =1;
    std::cin>>status;
    if(status==1){
      
      std::cout<<"Происходит создание кучек для игры..."<<std::endl;
      fill(game);
    }
    else{
      for(int i=0;i<n;i++){
        std::cin>>game[i];
      }
      
    }
    print(game);
    
    

    // Цикл игры
    while (true) {
        // Печатаем состояние куч
        

        // Ход игрока
        int number, stones;
        std::cout << "Your turn - Enter heap number"<<1<<" to "<<n<<std::endl;
        std::cin >> number;
        if(number>n || number<1){
          std::cout<<"Такой кучки у нас нет";
          continue;
        }
        std::cout << "Enter the number of stones you want to remove: ";
        
        
        std::cin >> stones;
        if(stones<1){
          std::cout<<"Введите натуральное число камней";
          continue;
        }
      
        // Обновляем состояние куч
        for (int i=0;i<n;i++){
          if(i==number-1){
            if(game[i]>=stones){
              game[i]-=stones;
            }
            else{
              std::cout<<"Введено неверное число камней"<<std::endl;
              continue;
            }
            break;
          }
        }

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
            std::cout<<"xor != 0 "<<xorSum<<std::endl;
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
            std::cout<<"xor = 0 "<<xorSum<<std::endl;
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
