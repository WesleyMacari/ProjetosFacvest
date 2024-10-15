import java.util.Scanner;
import java.util.Locale;

public class Renda {
    
    public static void main(String[] args) {
        Locale.setDefault(Locale.US);
        Scanner sc = new Scanner(System.in);

        double salarioAnual, servico, capital, medico, educacao, impSalario = 0, impServicos = 0, impCapital = 0, impBruto, impDevido, abatimento, gastos, maxDedutivel;

        System.out.printf("Renda anual com salario: ");
        salarioAnual = sc.nextDouble();
        System.out.printf("Renda anual com prestacao de servico: ");
        servico = sc.nextDouble();
        System.out.printf("Renda anual com ganho de capital: ");
        capital = sc.nextDouble();
        System.out.printf("Gastos medicos: ");
        medico = sc.nextDouble();
        System.out.printf("Gastos educacionais: ");
        educacao = sc.nextDouble();

        System.out.println("\nRELATORIO DE IMPOSTO DE RENDA\n");
        System.out.println("*CONSOLIDADO DE RENDA:");

        // Calculo para o Imposto sobre Salário    
        double salarioMensal = salarioAnual / 12;
        if (salarioMensal > 3000.0 && salarioMensal <= 5000.0) {
            impSalario = salarioAnual * 0.10;
        } else if (salarioMensal > 5000.0) {
            impSalario = salarioAnual * 0.20;
        }
        System.out.printf("\nImposto sobre salario: %.2f", impSalario);

        // Calculo para imposto sobre serviços
        if (servico > 0) {
            impServicos = servico * 0.15;
        }
        System.out.printf("\nImposto sobre servicos: %.2f", impServicos);

        // Calculo para imposto de ganho de capital
        if (capital > 0) {
            impCapital = capital * 0.20;
        }
        System.out.printf("\nImposto sobre ganho capital: %.2f\n", impCapital);

        System.out.println("\n*DEDUCOES: \n");

        // Calculo para Imposto Bruto
        impBruto = impSalario + impServicos + impCapital;
        
        // Calculo do máximo dedutível e dedução permitida
        gastos = medico + educacao;
        maxDedutivel = impBruto * 0.30;
        abatimento = Math.min(gastos, maxDedutivel);

        System.out.printf("Maximo dedutivel: %.2f", maxDedutivel);
        System.out.printf("\nGastos dedutiveis: %.2f\n", gastos);

        System.out.println("\nRESUMO:\n");

        System.out.printf("Imposto bruto total: %.2f", impBruto);
        System.out.printf("\nAbatimento: %.2f\n", abatimento);

        // Calculo para o imposto devido
        impDevido = impBruto - abatimento;
        System.out.printf("Imposto Devido: %.2f\n", impDevido);

        sc.close();
    }
}
