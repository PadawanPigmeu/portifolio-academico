module alu_control (
    input      [1:0] ALUOp,
    input      [5:0] funct,
    output reg [2:0] alu_ctrl
);
    always @(*) begin
        case (ALUOp)
            2'b00: alu_ctrl = 3'b010; // ADD (para LW, SW, ADDI)
            2'b01: alu_ctrl = 3'b110; // SUB (para BEQ)
            2'b10: begin             // Instruções Tipo R (dependem de funct)
                case (funct)
                    6'b100000: alu_ctrl = 3'b010; // ADD
                    6'b100010: alu_ctrl = 3'b110; // SUB
                    6'b100100: alu_ctrl = 3'b000; // AND
                    6'b100101: alu_ctrl = 3'b001; // OR
                    6'b101010: alu_ctrl = 3'b111; // SLT
                    default:   alu_ctrl = 3'b010;
                endcase
            end
            default: alu_ctrl = 3'b010;
        endcase
    end
endmodule