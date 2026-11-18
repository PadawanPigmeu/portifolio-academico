module ULA #(
    parameter WIDTH = 32
)(
    input  [WIDTH-1:0] a, b,
    input  [2:0]       alu_ctrl,
    output reg [WIDTH-1:0] result,
    output             zero,
    output reg         overflow
);
    assign zero = (result == {WIDTH{1'b0}});

    always @(*) begin
        result = {WIDTH{1'b0}};
        overflow = 1'b0;
        
        case(alu_ctrl)
            3'b000: result = a & b; 
            3'b001: result = a | b; 
            3'b010: begin 
                result = a + b;
                overflow = (~a[WIDTH-1] & ~b[WIDTH-1] &  result[WIDTH-1]) | 
                           ( a[WIDTH-1] &  b[WIDTH-1] & ~result[WIDTH-1]);
            end
            3'b110: begin 
                result = a - b;
                overflow = (~a[WIDTH-1] &  b[WIDTH-1] &  result[WIDTH-1]) | 
                           ( a[WIDTH-1] & ~b[WIDTH-1] & ~result[WIDTH-1]);
            end
            3'b111: begin 
                if (a[WIDTH-1] != b[WIDTH-1]) begin
                    result = { {(WIDTH-1){1'b0}}, a[WIDTH-1] };
                end else begin
                    result = (a < b) ? {{(WIDTH-1){1'b0}}, 1'b1} : {WIDTH{1'b0}};
                end
            end
            default: result = {WIDTH{1'b0}}; 
        endcase
    end
endmodule