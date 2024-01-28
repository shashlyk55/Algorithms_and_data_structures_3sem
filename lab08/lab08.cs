using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/*
1.	Разработать приложение, которые будет находить максимальную стоимость предметов, положенных в рюкзак, вместимость которого не более N. 
2.	Пользователь вводит N, товары (название, вес товара и стоимость товара). 
3.	Приложение должно вывести какие предметы были положены в рюкзак и максимальную их стоимость.  
*/

namespace lab08
{
    internal class Item
    {
        public int Weight;
        public string Name;
        public int Cost;
        public Item()
        {

        }
        public Item(string name, int weight, int cost)
        {
            Weight = weight;
            Name = name;
            Cost = cost;
        }

        public override string ToString()
        {
            return $"{Name} Цена: {Cost} Вес: {Weight}";
        }
    }
    internal class Program
    {
        static void Main()
        {
            var list = new List<Item>();
            Console.WriteLine("Вместимость сумки: ");
            int N = 30;
            //N = Convert.ToInt32(Console.ReadLine());
            var item1 = new Item("qwe", 12, 35);
            var item2 = new Item("rty", 5, 20);
            var item3 = new Item("ujn", 10, 17);
            var item4 = new Item("yfs", 8, 12);
            var item5 = new Item("asd", 21, 33);
            list.Add(item1);
            list.Add(item2);
            list.Add(item3);
            list.Add(item4);
            list.Add(item5);
            var bag = new List<Item>();
            bool flag = true;
            int weight, cost;
            string name;
            int sum = 0;
            /*Console.WriteLine("Введите предметы(для остановки введите END): ");
            while (flag)
            {
                var item = new Item();
                Console.WriteLine("Введите название предмета: ");
                name = Console.ReadLine();
                if (name == "END")
                {
                    flag = false;
                    break;
                }
                Console.WriteLine("Введите вес предмета: ");
                weight = Convert.ToInt32(Console.ReadLine());
                Console.WriteLine("Введите стоимость предмета: ");
                cost = Convert.ToInt32(Console.ReadLine());
                item.Name = name;
                item.Weight = weight;
                item.Cost = cost;
                list.Add(item);
            }*/
            Console.WriteLine();
            foreach (var obj in list)
            {
                Console.WriteLine(obj.ToString());
            }
            foreach(var obj in list)
            {
                if(obj.Weight > N)
                    list.Remove(obj);
            }
            while(true)
            {
                var a = list.Find(i => i.Cost == list.Max(j => j.Cost));
                if (a.Weight <= N)
                {
                    bag.Add(a);
                    list.Remove(a);
                    N-=a.Weight;
                    sum+=a.Cost;
                }
                else list.Remove(a);

                if(list.Count == 0) break;
                

            }

            Console.WriteLine("Сумка:");
            foreach(var obj in bag)
            {
                Console.WriteLine(obj.ToString());
            }

        }
    }
}
