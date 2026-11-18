module memoriaInstrucoes (
    input  [31:0] endereco,
    output [31:0] instrucao
);
    reg [31:0] rom [0:63];
    integer i;

    initial begin
        for (i = 0; i < 64; i = i + 1) begin
            rom[i] = 32'h00000000;
        end
       
        rom[0] = 32'h11090001; // End 0:  beq  $8, $9, 1   (op=4, rs=8, rt=9, imm=1)
        rom[1] = 32'h21080002; // End 4:  addi $8, $8, 2   (op=8, rs=8, rt=8, imm=2)
        rom[2] = 32'hAD880000; // End 8:  sw   $8, 0($12)  (op=43, rs=12, rt=8, imm=0)
        rom[3] = 32'h8D900000; // End 12: lw   $16, 0($12) (op=35, rs=12, rt=16, imm=0)
        rom[4] = 32'h020A4022; // End 16: sub  $8, $16, $10(op=0, rs=16, rt=10, rd=8, funct=34)
        rom[5] = 32'h08000000; // End 20: j    0           (op=2, target=0)
    end

    assign instrucao = rom[endereco[7:2]];
endmodule