module memoriaDados #(
    // Parâmetros permitem configurar o tamanho do módulo ao instanciá-lo no top-level.
    parameter DATA_WIDTH = 32, // Define que cada palavra gravada terá 32 bits (padrão MIPS).
    parameter ADDR_WIDTH = 5   // Define que o endereço tem 5 bits, criando 32 posições de memória (2^5).
)(
    // Declaração das portas de entrada e saída (conexões com o datapath)
    input [ADDR_WIDTH-1:0] address,   // Fio do endereço: vem da saída da ULA
    input memWrite,                   // Fio de controle de escrita: vem da Unidade de Controle
    input memRead,                    // Fio de controle de leitura: vem da Unidade de Controle
    input clock,                      // Fio do clock principal do sistema.
    input [DATA_WIDTH-1:0] writeData, // Fio com o dado a ser salvo
    output reg [DATA_WIDTH-1:0] readData // Fio com o dado lido
);

    // Criação da matriz que simula o chip de memória RAM fisicamente.
    reg [DATA_WIDTH-1:0] memory [0:(1<<ADDR_WIDTH)-1];
    integer i;

    // Bloco sequencial para ESCRITA (Síncrono).
    always @(posedge clock) begin
        if (memWrite) begin
            memory[address] <= writeData;
        end
    end

    // Bloco inicial (Configuração de arranque)
    initial begin
        // Zera toda a memória primeiro para evitar lixo residual
        for (i = 0; i < (1<<ADDR_WIDTH); i = i + 1) begin
            memory[i] = 32'd0; 
        end

        // Grava no índice convertido (Word Address - divisão por 4)
        memory[6] = 32'd6; 
        memory[7] = 32'd3; 

        // Grava no índice absoluto caso o descarte de bits no Top-Level esteja desligado
        memory[24] = 32'd6; 
        memory[28] = 32'd3; 
    end

    // Bloco combinacional para LEITURA (Assíncrono).
    always @(*) begin
        if (memRead) begin
            readData = memory[address];
        end else begin
            readData = {DATA_WIDTH{1'b0}}; 
        end
    end
endmodule