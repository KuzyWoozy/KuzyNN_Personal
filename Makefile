


compile: 
	@g++ -o exec.out -I FileReader -I KuzyMatrix -I KuzyNN test.cpp

run: compile
	@./exec.out
	

clean:
	@rm -f *.out
	@rm -f FileReader/*.gch
	@rm -f KuzyMatrix/*.gch
	@rm -f KuzyNN/*.gch
	@rm -f *.gch
