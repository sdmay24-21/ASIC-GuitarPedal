module mux(
    input [15:0] a,
    input [15:0] b,
    input s,
    output reg [15:0] out
);

always @(*) begin
    if (s)
        out = b;
    else
        out = a;
end

endmodule
