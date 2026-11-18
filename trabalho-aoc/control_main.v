module control_main (
    input      [5:0] opcode,
    output reg       RegDst,
    output reg       ALUSrc,
    output reg       MemtoReg,
    output reg       RegWrite,
    output reg       MemRead,
    output reg       MemWrite,
    output reg       Branch,
    output reg       Jump,  
    output reg [1:0] ALUOp 
);
    always @(*) begin 
        RegDst   = 1'b0;
        ALUSrc   = 1'b0;
        MemtoReg = 1'b0;
        RegWrite = 1'b0;
        MemRead  = 1'b0;
        MemWrite = 1'b0;
        Branch   = 1'b0;
        Jump     = 1'b0;       // Padrão inativo
        ALUOp    = 2'b00;

        case (opcode)
            6'b000000: begin // Tipo R (add, sub, and, or, slt)
                RegDst   = 1'b1; 
                ALUSrc   = 1'b0; 
                MemtoReg = 1'b0; 
                RegWrite = 1'b1; 
                ALUOp    = 2'b10; 
            end
            6'b001000: begin // ADDI
                RegDst   = 1'b0; 
                ALUSrc   = 1'b1; 
                MemtoReg = 1'b0; 
                RegWrite = 1'b1; 
                ALUOp    = 2'b00; 
            end
            6'b100011: begin // LW
                RegDst   = 1'b0; 
                ALUSrc   = 1'b1; 
                MemtoReg = 1'b1; 
                RegWrite = 1'b1; 
                MemRead  = 1'b1; 
                ALUOp    = 2'b00; 
            end
            6'b101011: begin // SW
                ALUSrc   = 1'b1; 
                MemWrite = 1'b1; 
                ALUOp    = 2'b00; 
            end
            6'b000100: begin // BEQ (Branch on Equal)
                ALUSrc   = 1'b0; 
                Branch   = 1'b1; // Ativa linha de Branch
                ALUOp    = 2'b01; // ULA faz SUB para comparar
            end
            6'b000010: begin // NOVO: J (Jump Incondicional)
                Jump     = 1'b1; // Ativa o MUX de Jump
            end
            default: ; 
        endcase
    end
endmodule