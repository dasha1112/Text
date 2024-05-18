#include "TWord.h"
#include "TText.h"
int main() 
{
	TText res;
	TLine line;
	TPage page;
	std::string s = "POEM ABOUT LITTLE TURTLE\nI am a little turtle,\nI crawl so slow,\nAnd carry my house\nWherever I go.\nWhen I get tired\nI pull in my head,\nMy legs and my tail,\nAnd go to bed!";
	res = res.CreateText(s);
	std::cout << "Original text\n" << res;

	line = res.FindLine("house");
	std::cout << "\nLets find a line that contains the word 'house'\n\n" << line.GetData() << "\n";

	res.InsertWord("And carry my house", "house", "beautiful");
	res.Delete("I am a little turtle,", "little");
	std::cout << "\nLets insert the word 'beautiful' before the word 'house' and delete the word 'little' in string 'I am a little turtle,'\n\n" << res << "\n";

	TText text;
	std::string str = "TEXT ABOUT CATS\nUKNOWN AUTOR\nWRITTEN JANUARY 18, 2023\nCats are wonderful pets that many people love. They come in different colors and sizes. Cats are known for being playful and sometimes a bit lazy. These furry friends have soft paws and sharp claws. They use their claws for various things, like scratching to keep their claws healthy and marking their territory. Cats also have a special ability to land on their feet if they fall, which is really impressive. Cats enjoy their independence. They often like to explore their surroundings and might hide in cozy spots. They clean themselves by licking their fur and are usually very clean animals. Cats like to communicate with us using different sounds, like meowing, purring, and even hissing if they’re scared. They also use their tails to show how they feel. A wagging tail might mean they’re excited, while a puffed-up tail can mean they’re scared. Playing with cats using toys like balls or strings is lots of fun, and it keeps them active. They also like to nap a lot during the day. If you’re thinking of having a cat as a pet, remember to give them love, care, and a cozy place to sleep. In short, cats are lovely pets with soft fur and sharp claws. They’re independent, playful, and great at keeping clean. Cats talk to us with sounds and tails, and they enjoy playing and napping. If you have a cat, make sure to give them care and affection. If you are a good ouner, than cats would love you.\n\nTEXT ABOUT MOUSE\nAUTOR IS SERGEY\nMice are good at living in various places such as fields, forests, and even in houses. They are quite clever and can fit through small spaces to find food and shelter. Mice like to eat seeds, grains, and sometimes even bits of food people leave behind. These little creatures have a lot of babies at once, called pups. Pups are born blind and without fur, but they grow quickly. Cats, owls, and other animals like to catch mice for food, so mice must be careful to stay safe.";
	text = text.CreateText(str);
	std::cout << "\n" << text;

	page = text.FindPage("TEXT ABOUT MOUSE");
	std::cout << "\nLets find a page that contains the line 'TEXT ABOUT MOUSE'\n" << page;
	TPage newPage;
	text.DeleteLine(2, 3);
	text.InsertLine(2, 3, "WRITTEN AUGUST 11, 2022");
	std::cout << "\nLets delete line 'AUTOR IS SERGEY' and insert 'WRITTEN AUGUST 11, 2022'\n\n" << text;
	//std::cout << "\nLets delete the word 'little' in string 'I am a little turtle,'\n" << res;
	//res.InsertWord("My name is Dasha", "name", "a");
	//res.InsertLine(1, 2, "How are you?");
	//
	//res.Delete("Nice to meet you!", "to");
	//res.DeleteLine(1, 2);
	//res.AddLine("Bye!");
	//std::cout << res;

	//line = res.FindLine("Hello"); // найти строку
	//page = res.FindPage("Hello world");

	//std::cout <<"\n\nThe founded line is: " << line.GetData();
	//std::cout << "\n\nThe founded page is: " << page;
	return 0;
}