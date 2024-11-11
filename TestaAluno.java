import java.util.Scanner;

public class TestaAluno {
	
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Aluno aluno = new Aluno();

        System.out.println(">>> INÍCIO SOFTWARE ALUNO <<<");
        
        
        System.out.print("Informe o nome do aluno: ");
        aluno.setNome(scanner.nextLine());
        
        System.out.print("Informe a matrícula: ");
        aluno.setMatricula(scanner.nextLine());

        System.out.print("Informe o sexo: ");
        aluno.setSexo(scanner.next().charAt(0));
        scanner.nextLine();
        
        System.out.print("Informe a data de nascimento: ");
        aluno.setDataNascimento(scanner.nextLine());

        System.out.print("Informe o Curso: ");
        aluno.setCurso(scanner.nextLine());

        System.out.print("Informe o ano de início: ");
        aluno.setAnoInicio(scanner.nextInt());

        System.out.print("Informe a Nota da Prova 1: ");
        aluno.setNotaProva1(scanner.nextDouble());

        System.out.print("Informe a Nota da Prova 2: ");
        aluno.setNotaProva2(scanner.nextDouble());

        System.out.print("Informe a média dos Trabalhos: ");
        aluno.setMediaTrabalhos(scanner.nextDouble());
        System.out.println();
        
        System.out.println("### INFORMAÇÕES ###");
        System.out.println("Nome: " + aluno.getNome());
        System.out.println("Matrícula: " + aluno.getMatricula());
        System.out.println("Nome do curso: " + aluno.getCurso());

        
        double mediaFinal = aluno.calcularMediaFinal();
        String situacao = aluno.isAprovado() ? "Aprovado" : "Reprovado";
        System.out.printf("Situação: %s com média %.2f%n", situacao, mediaFinal);

        System.out.println(">> Fim da execução do software <<<");

        scanner.close();
    }
}