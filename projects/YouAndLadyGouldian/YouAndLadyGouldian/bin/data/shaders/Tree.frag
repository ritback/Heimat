#version 150

uniform vec3            uResolution;           // viewport resolution (in pixels)
uniform float           uGlobalTime;           // shader playback time (in seconds)

uniform float           uAlpha;
uniform vec3            uOnScreenPos;
uniform vec3            uTreeSize;
uniform vec3            uMouse;

in vec2 iFragCoord; // coordinate in pixel.
in vec2 iChannelCoord0;

out vec4 oColor;




// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// Can add more if your GPU can handle it! :)
#define LEAFS 8
#define BRANCHES 6
#define TRUNKS 6


///////////////////////////////////////////
///////////////////////////////////////////
const float PI = 3.14159265;
const float WSCALE = 0.8;
//#define T (uGlobalTime*0.5)
const float LEAF = 1.0;
const float TRUNK = 2.0;

vec2 seed;
vec2 im;

//http://iquilezles.org/www/articles/smin/smin.htm
float smin( float a, float b )
{
    float k = 0.003;
    float h = clamp( 0.5+0.5*(b-a)/k, 0.0, 1.0 );
    return mix( b, a, h ) - k*h*(1.0-h);
}

float rand(vec2 co)
{
    co += im.xy + seed;
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float rand1(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}


vec2 rotate(vec2 point, float angle)
{
    float x = point.x; float y = point.y;
    float ca = cos(angle);
    float sa = sin(angle);
    point.x = x * ca - y * sa;
    point.y = y * ca + x * sa;
    return point;
}

float sdTreePart(vec2 pos, vec2 uv, vec2 pivot, float angle, float w, float h)
{
    uv -= pos;
    uv = rotate(uv, angle) + pivot;
    
    float b = WSCALE + smoothstep(0.0, -h * 2., uv.y - h) * (1.0 - WSCALE);
    w *= b;
    
    float y = max(uv.y - h, -h - uv.y);
    float x = max(uv.x - w, -w - uv.x);
    
    return max(x, y);
}


float sdLeaf(vec2 pos, vec2 uv, vec2 pivot, float angle, float w, float h)
{
    uv -= pos;
    uv = rotate(uv, angle) + pivot;
    
    w -= -0.0005;//cos(uv.y * 500.) * 0.001; //smaller the bigger
    h -= 0.0005;//sin(uv.x * 500.) * 0.002;
    float y = max(uv.y - h, -h - uv.y);
    float x = max(uv.x - w, -w - uv.x);
    
    return max(x, y);
}


float Cursor(in vec2 uv, inout vec2 pos, float H, inout float angle, inout float W)
{
    seed += vec2(0.01, 0.04);
    W *= WSCALE;
    vec2 pivot = vec2(0.0, -H);
    float b = sdTreePart(pos, uv, pivot, angle, W, H);
    pos += vec2(sin(angle), cos(angle)) * H * 2.;
    float r = rand(seed);
    angle += (r - 0.5) * 0.9;
    return b;
}

int leafIndex = 0;

vec2 Tree (vec2 pos, vec2 uv)
{
    float H = 0.02;
    vec2 pivot = vec2(0.0, -H);
    float b = 999.0;
    float angle = 0.0;
    float W = 0.01;
    
    float randH = 0.5 * (rand(im.xy) - 0.5);
    float randA = rand(im.yx) - 0.5;
    float lf = 999.0;
    float LEAFANGLE = PI * 0.2;
    vec2 leafSize = vec2(0.005, 0.01);
    
    for (int i = 0; i < TRUNKS; ++i)
    {
        b = smin(b, Cursor(uv, pos, H, angle, W));
        /*
        vec2 p = pos;
        float h = H;
        float a = randA + angle + sin((uGlobalTime*0.5) + float(i)) * 0.1;
        float w = W;
        
        for (int j = 0; j < BRANCHES; ++j)
        {
            b = smin(b, Cursor(uv, p, h, a, w));
            
            vec2 p1 = p;
            float h1 = max(randH * 0.06, 0.006);
            float a1 = randA + a + sin((uGlobalTime*0.5) + float(j) * 0.4) * 0.1;
            float w1 = w;
            
            for (int k = 0; k < LEAFS; ++k)
            {
                b = smin(b, Cursor(uv, p1, h1, a1, w1));
                float angl = mod(float(k), 2.0)  == 0.0 ? 1.0 : -1.0;
                
                float newLeaf = sdLeaf(p1, uv, vec2(0.0, -leafSize.y),  (a1 + angl * LEAFANGLE), leafSize.x, leafSize.y);
                if(newLeaf < lf) leafIndex = i * 100 + j * 10 + k;
                lf = min(lf, newLeaf);
                if(lf < 0.0 || b < 0.0) break;
            }
            if(lf < 0.0 || b < 0.0) break;
        }
        if(lf < 0.0 || b < 0.0) break;
        */
    }
    if(b < lf)
    {
        return vec2(TRUNK, b);
    }
    return vec2(LEAF, lf);
}


// -----------------------------------------------------------------------------

const float heatAmount = 0.04;

void main()
{
    //vec2 p = iFragCoord.xy / uResolution.xy;
	//float phase = uGlobalTime * 0.1;
    
    im = vec2(0, 0);//uOnScreenPos.xy;
    
    
    vec2 uv = (iFragCoord - uResolution.xy / 2) / uResolution.xy;
    
    //vec2 uv = iFragCoord.xy / uResolution.xy;
    //uv -= vec2(0.5);
    //uv.y /= uResolution.xy.x / uResolution.xy.y;
    
    
    vec2 pos = uMouse.xy;//vec2(0.0, -0.5);
    vec2 material = Tree(pos, uv);
    
    
    float t = material.y / 0.001;
    t = clamp(t, -0.1, 1.0);
    
    
    vec4 col = vec4(material.y);
    
    col = smoothstep(.5, 0.0, col);
    
    
    if(material.x == LEAF)
    {
        float leafCol = sin(float(leafIndex) * .5) * 0.5 + 0.5;
        leafCol = mix(leafCol, 1.0, 0.5);
        col = vec4(leafCol) * vec4(0.4, 0.7, 0.1, 0.0);
    }
    else if (material.x == TRUNK)
    {
        col *= vec4(.8, 0.7, 0.3, 0.0);
    }
    
    oColor = vec4(0);
    oColor = mix(col, oColor, t);
    
    //oColor = vec4(255, 0, 0, uAlpha);
}






