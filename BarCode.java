import java.util.Scanner;

public class BarCode {
	public static void main(String[] args) {
	
	Scanner sc = new Scanner(System.in);
	
	char sexo;
	double ingresso, valorRefri, valorEspetinho, valorGelada, valorTotal, valorCourvet;
	int refri, gelada, espetinho;
	
	valorRefri = 3.0;
	valorGelada = 5.0;
	valorEspetinho = 7.0;
	valorCourvet = 4.0;
	
	System.out.printf("Sexo(F/M): ");
	sexo = sc.next().charAt(0);
	System.out.printf("Quantidade de refrigerantes: ");
	refri = sc.nextInt();
	System.out.printf("Quantidade de cervejas: ");
	gelada = sc.nextInt();
	System.out.printf("Quantidade de espetinhos: ");
	espetinho = sc.nextInt();
	
	ingresso = (sexo == 'F' || sexo == 'f') ? 8.0 : 10.0;
	
	System.out.println("\nRelatorio:\n");
	
	double consumo = (refri * valorRefri) + (gelada * valorGelada) + (espetinho * valorEspetinho);
	System.out.printf("Consumo: R$ %.2f", consumo);
	
	if (consumo > 30) {
		valorCourvet = 0;
	}
	
	System.out.printf("\nCouvert = R$ %.2f\n", valorCourvet);
	System.out.printf("Ingresso = R$ %.2f\n", ingresso);
	System.out.println();
	valorTotal = consumo + valorCourvet + ingresso;
	System.out.printf("Valor a pagar = R$ %.2f\n", valorTotal);
 }
}