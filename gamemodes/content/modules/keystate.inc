public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CTRL_BACK)
    {
        new params[1];
        cmd_entrar(playerid, params);
    }
    return 1;
}