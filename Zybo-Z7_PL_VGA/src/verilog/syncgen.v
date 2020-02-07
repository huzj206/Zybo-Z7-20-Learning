/* Copyright(C) 2016 Cobac.Net All Rights Reserved. */
/* chapter: ��2��          */
/* project: pattern        */
/* outline: �����M���쐬   */

module syncgen(
    input               CLK,
//    input               RST,
    output              PCK,
    output  reg         VGA_HS,
    output  reg         VGA_VS,
    output  reg [9:0]   HCNT,
    output  reg [9:0]   VCNT
);

/* VGA(640�~480)�p�p�����[�^�ǂݍ��� */
`include "vga_param.vh"

/* MMCM��ڑ�����PCK�𐶐� */
pckgen pckgen ( .SYSCLK(CLK), .PCK(PCK) );

/* �����J�E���^ */
wire hcntend = (HCNT==HPERIOD-10'h001);

always @( posedge PCK ) begin
//    if ( RST )
//        HCNT <= 10'h000;
    if ( hcntend )
        HCNT <= 10'h000;
    else
        HCNT <= HCNT + 10'h001;
end

/* �����J�E���^ */
always @( posedge PCK ) begin
//    if ( RST )
//        VCNT <= 10'h000;
    if ( hcntend ) begin
        if ( VCNT == VPERIOD - 10'h001 )
            VCNT <= 10'h000;
        else
            VCNT <= VCNT + 10'h001;
    end
end

/* �����M�� */
wire [9:0] hsstart = HFRONT - 10'h001;
wire [9:0] hsend   = HFRONT + HWIDTH - 10'h001;
wire [9:0] vsstart = VFRONT;
wire [9:0] vsend   = VFRONT + VWIDTH;

always @( posedge PCK ) begin
//    if ( RST )
//        VGA_HS <= 1'b1;
    if ( HCNT==hsstart )
        VGA_HS <= 1'b0;
    else if ( HCNT==hsend )
        VGA_HS <= 1'b1;
end

always @( posedge PCK ) begin
//    if ( RST )
//        VGA_VS <= 1'b1;
    if ( HCNT==hsstart ) begin
        if ( VCNT==vsstart )
            VGA_VS <= 1'b0;
        else if ( VCNT==vsend )
            VGA_VS <= 1'b1;
    end
end

endmodule
