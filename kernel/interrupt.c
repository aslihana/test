void encodeGdtEntry(uint8_t *target, struct GDT source)
{
    if ((source.limit > 65536) && ((source.limit & 0xFFF) != 0xFFF)) 
    {
        kerror("You can't do that!");
    }
    if (source.limit > 65536) 
    {
        // Adjust granularity if required
        source.limit = source.limit >> 12;
        target[6] = 0xC0;
    } 
    
    else 
    {
        target[6] = 0x40;
    }
 
    // limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] |= (source.limit >> 16) & 0xF;
 
    // base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;
 
    // type
    target[5] = source.type;
}
