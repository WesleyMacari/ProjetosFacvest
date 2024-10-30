import java.util.Scanner;
import java.util.Locale;

public class codeConcurso {
	
    public static void main(String[] args) {
		
    	
    	Scanner sc = new Scanner(System.in);
    	Locale.setDefault(Locale.US);
    	
    	System.out.printf("Qual a quantidade de pessoas? ");
    	int N = sc.nextInt();
    	sc.nextLine();
    	
    	String[] nomes = new String[N];
    	double[] nota1 = new double[N];
    	double[] nota2 = new double[N];
    	double[] medias = new double[N];
    	
    	double mediaMaior = 0;
    	String nomeMediaMaior = "";
    	int aprovados = 0;
    	double somaAprovados = 0;
    
    	for(int i = 0; i < N; i++) {
    		
    		System.out.println("Digite os dados da " + (i + 1) + "a pessoa: ");
    		System.out.print("Nome: ");
    		nomes[i] = sc.nextLine();
    		sc.nextLine();
    		
    		//AVISO: QUANDO FOR COLOCAR OS VALORES DECIMAIS COLOQUE "," AO EM VEZ DE "."!!!
    		System.out.printf("Nota etapa 1: ");
    		nota1[i] = sc.nextDouble();
    		sc.nextLine();
    		System.out.printf("Nota etapa 2: ");
    		nota2[i] = sc.nextDouble();
    		sc.nextLine();
    		
    		medias[i] = (nota1[i] + nota2[i]) / 2.0;
    		
    		if (medias[i] >= 70) {
    			aprovados++;
    			somaAprovados += medias[i];
    		}
    		
    		if(medias[i] > mediaMaior) {
    			mediaMaior = medias[i];
    			nomeMediaMaior = nomes[i];
    		}
    	}
    	
    	System.out.println("\nTABELA:\n");
    	
    	for(int i = 0; i < N; i++) {
    		System.out.printf("%s - %.2f - %.2f - MEDIA = %.2f\n", nomes[i], nota1[i], nota2[i], medias[i]);
    	}
    	
    	System.out.println("\nPESSOAS APROVADAS:");
    	if (aprovados == 0) {
    		System.out.println("Nao ha candidatos aprovados!");
    	} else {
    		for (int i = 0; i < N; i++) {
    			if (medias[i] >= 70) {
    				System.out.println(nomes[i]);
    			}
    		}
        }
    	
    	//Calculo da porcentagem dos aprovados
    	double porcAprovados = ((double) aprovados / N) * 100;
    	System.out.printf("\nPorcentagem de aprovacao: %.2f%%\n", porcAprovados);
    	
    	
    	System.out.printf("\nPessoa com maior media: %s\n", nomeMediaMaior);
    	
    	if(aprovados > 0) {
    		double mediaAprovados = somaAprovados / aprovados;
    		System.out.printf("\nMedia das notas dos aprovados: %.2f\n", mediaAprovados);
    	} else {
    		System.out.println("\nNao ha candidatos aprovados!");
    	}
    	
    	sc.close();
    }
    	
}
