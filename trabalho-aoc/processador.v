module processador ( 
    input  [1:0]  KEY,      
    input  [9:0]  SW,       
    output [9:0]  LEDR,     
    output [6:0]  HEX0, HEX1, HEX2, HEX3, HEX4, HEX5 
);
    
	 wire manual_clk = ~KEY[0];
	 //wire manual_clk = SW[9];
    wire manual_rst = ~KEY[1];

    wire [31:0] pc_val, instr_val, rdata1, rdata2, ula_res, wdata_reg;
    wire        zero_flag, ovf_flag;
    wire [7:0]  id_operacao_visual;

    mips_core core (
        .clock(manual_clk),                                      
        .reset(manual_rst),                                      
        .pc_out(pc_val),                                        
        .instruction(instr_val),
        .read_data1(rdata1),
        .read_data2(rdata2),
        .alu_result(ula_res),
        .write_data_reg_out(wdata_reg), // novo fio do write data
        .zero(zero_flag),
        .overflow(ovf_flag),
        .id_operacao(id_operacao_visual)
    );

    reg [15:0] display_data;

    always @(*) begin
        case (SW[2:0])
            3'b000: display_data = pc_val[15:0];    // 000: PC
            3'b001: display_data = rdata1[15:0];    // 001: ReadData1
            3'b010: display_data = rdata2[15:0];    // 010: ReadData2 / WriteDataMem
            3'b011: display_data = ula_res[15:0];   // 011: ALUResult
            3'b100: display_data = instr_val[15:0]; // 100: Instrução bruta (16 bits baixos)
            3'b101: display_data = wdata_reg[15:0]; // 101  WriteDataRegs (Dado indo pro BR)
            default: display_data = 16'h0000;
        endcase
    end

    decodificador_7seg d5 (.A(id_operacao_visual[7]), .B(id_operacao_visual[6]), .C(id_operacao_visual[5]), .D(id_operacao_visual[4]), .seg(HEX5));
    decodificador_7seg d4 (.A(id_operacao_visual[3]), .B(id_operacao_visual[2]), .C(id_operacao_visual[1]), .D(id_operacao_visual[0]), .seg(HEX4));

    decodificador_7seg d3 (.A(display_data[15]), .B(display_data[14]), .C(display_data[13]), .D(display_data[12]), .seg(HEX3));
    decodificador_7seg d2 (.A(display_data[11]), .B(display_data[10]), .C(display_data[9]),  .D(display_data[8]),  .seg(HEX2));
    decodificador_7seg d1 (.A(display_data[7]),  .B(display_data[6]),  .C(display_data[5]),  .D(display_data[4]),  .seg(HEX1));
    decodificador_7seg d0 (.A(display_data[3]),  .B(display_data[2]),  .C(display_data[1]),  .D(display_data[0]),  .seg(HEX0));

    assign LEDR[0]   = zero_flag; // Flag Zero da ULA
    assign LEDR[1]   = ovf_flag;  
    assign LEDR[9:2] = 8'b00000000; 
endmodule