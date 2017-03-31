require('readobj')
-- CS488 -- Introduction to Computer Graphics
-- 
-- a3mark.lua
--
-- A very simple scene creating a trivial puppet.  The TAs will be
-- using this scene as part of marking your assignment.  You'll
-- probably want to make sure you get reasonable results with it!

node = gr.node('node')



rootnode = gr.node('root')
node:add_child(rootnode)
rootnode:rotate('y', 50)
rootnode:scale(1.0,0.7,1.0)

red = gr.material({1.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
blue = gr.material({0.0, 0.0, 1.0}, {0.1, 0.1, 0.1}, 10)
green = gr.material({0.0, 1.0, 0.0}, {0.1, 0.1, 0.1}, 10)
white = gr.material({0.6, 1.0, 1.0}, {0.1, 0.1, 0.1}, 10)
black = gr.material({0.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)

--rootnode:rotate('z',50)
torsojoint = gr.joint('torsojoint', {0, 0, 0}, {0, 0, 0})
rootnode:add_child(torsojoint)


--torso!
s0 = gr.sphere('s0')
s0:scale(1.0,2.0,1.0)
torsojoint:add_child(s0)
s0:set_material(white)

--shoulder!


shoulderjoint = gr.joint('shoulderjoint', {0,0,0},{0,0,0})
rootnode:add_child(shoulderjoint)
shoulderjoint:translate(0.0, 2.0, 0.0)

s1 = gr.sphere('s1')
shoulderjoint:add_child(s1)
s1:scale(2.0, 0.5, 1.0)
s1:set_material(white)



neckjoint=gr.joint('neckjoint', {-30, 0, 30}, {-30, 0, 30})
shoulderjoint:add_child(neckjoint)

sneck = gr.sphere('sneck')
neckjoint:add_child(sneck)
sneck:scale(0.5, 0.5, 0.4)
sneck:translate(0.0,1.5,0.0)
sneck:set_material(gr.material({0.8, 0.9, 0.8}, {0.1, 0.1, 0.1}, 10))



headjoint=gr.joint('headjoint', {-30, 0, 30}, {-30, 0, 30})
neckjoint:add_child(headjoint)
headjoint:translate(0.0, 1.8, 0.0)
--headjoint:rotate('y',90)


shead=gr.sphere('shead')
headjoint:add_child(shead)
shead:set_material(gr.material({0.8, 0.8, 0.9}, {0.1, 0.1, 0.1}, 10))


snose = gr.sphere('snose')
shead:add_child(snose)
snose:scale(0.2,0.2,0.2)
snose:translate(0.0,0.0,5.1)
snose:set_material(red)




--left arm!!
jla1 = gr.joint('jla1', {-180, 0, 180}, {0, 0, 0})
shoulderjoint:add_child(jla1)
jla1:translate(-1.8,0.0,0.0)
jla1:rotate('x',-90)

mla1=gr.material({0.8, 0.9, 0.9}, {0.1, 0.1, 0.1}, 10)
mla2=gr.material({0.9, 0.8, 0.8}, {0.1, 0.1, 0.1}, 10)
mla3=gr.material({0.9, 0.8, 0.9}, {0.1, 0.1, 0.1}, 10)
mll1=gr.material({0.9, 0.9, 0.8}, {0.1, 0.1, 0.1}, 10)
mll2=gr.material({0.9, 0.9, 0.9}, {0.1, 0.1, 0.1}, 10)
mll3=gr.material({0.8, 0.8, 0.8}, {0.1, 0.1, 0.1}, 10)

la1 = gr.sphere('la1')
jla1:add_child(la1)
la1:translate(0.0,-0.7,0.0)
la1:scale(0.3,0.7,0.3)
la1:set_material(mla1)


jla2 = gr.joint('jla2', {-180, 0, 180}, {0, 0, 0})
jla1:add_child(jla2)
jla2:translate(0.0,-1.3,0.0)
--jla2:rotate('z',-90)

la2 = gr.sphere('la2')
jla2:add_child(la2)
la2:scale(0.2,0.7,0.2)
la2:translate(0.0,-0.9,0.0)
la2:set_material(mla2)

jla3 = gr.joint('jla3', {-180, 0, 180}, {0, 0, 0})
jla2:add_child(jla3)
jla3:translate(0.0,-1.4,0.0)


la3 = gr.sphere('la3')
jla3:add_child(la3)
la3:scale(0.2,0.2,0.2)
la3:translate(0.0,-0.5,0.0)
la3:set_material(mla3)

--right arm!!


jra1 = gr.joint('jra1', {-180, 0, 180}, {0, 0, 0})
shoulderjoint:add_child(jra1)
jra1:translate(1.8,0.0,0.0)
--jra1:rotate('x',80)
--jra1:rotate('z',-90)



ra1 = gr.sphere('ra1')
jra1:add_child(ra1)
ra1:translate(0.0,-0.7,0.0)
ra1:scale(0.3,0.7,0.3)
ra1:set_material(mla1)


jra2 = gr.joint('jra2', {-180, 0, 180}, {0, 0, 0})
jra1:add_child(jra2)
jra2:translate(0.0,-1.3,0.0)
--jra2:rotate('z',-90)

ra2 = gr.sphere('ra2')
jra2:add_child(ra2)
ra2:scale(0.2,0.7,0.2)
ra2:translate(0.0,-0.9,0.0)
ra2:set_material(mla2)

jra3 = gr.joint('jra3', {-180, 0, 180}, {0, 0, 0})
jra2:add_child(jra3)
jra3:translate(0.0,-1.4,0.0)

ra3 = gr.sphere('ra3')
jra3:add_child(ra3)
ra3:scale(0.2,0.2,0.2)
ra3:translate(0.0,-0.5,0.0)
ra3:set_material(mla3)

--hip!
s2 = gr.sphere('s2')
rootnode:add_child(s2)
s2:translate(0.0, -2.0, 0.0)
s2:scale(1.5, 0.5, 1.0)
s2:set_material(white)

hipjoint = gr.joint('hipjoint', {0,0,0},{0,0,0})
rootnode:add_child(hipjoint)
hipjoint:translate(0.0,-2.0,0.0)

--left leg!
jll1 = gr.joint('jll1', {-180, 0, 180}, {0, 0, 0})
hipjoint:add_child(jll1)
jll1:translate(-1.0, 0.0, 0.0)
jll1:rotate('x', -30)
jll1:rotate('z', -40)
--jll1:rotate('z',-90)


ll1 = gr.sphere('ll1')
jll1:add_child(ll1)
ll1:scale(0.4,1.0,0.4)
ll1:translate(0.0,-1.0,0.0)
ll1:set_material(mll1)

jll2 = gr.joint('jll2', {-180, 0, 180}, {0, 0, 0})
jll1:add_child(jll2)
jll2:translate(0.0,-2.0,0.0)
jll2:rotate('x', 30)
jll2:rotate('z',30)
--jll2:rotate('z'90)

ll2 = gr.sphere('ll2')
jll2:add_child(ll2)
ll2:scale(0.4,0.8,0.4)
ll2:translate(0.0,-0.8,0.0)
ll2:set_material(mll2)

jll3 = gr.joint('jll3', {-180, 0, 180}, {0, 0, 0})
jll2:add_child(jll3)
jll3:translate(0.0,-1.4,0.0)
jll3:rotate('y',90)
jll3:rotate('z',-90)


ll3 = gr.sphere('ll3')
jll3:add_child(ll3)
ll3:scale(0.2,0.5,0.2)
ll3:translate(0.0,-0.5,0.0)
ll3:set_material(mll3)

--right leg!
jrl1 = gr.joint('jrl1', {-180, 0, 180}, {0, 0, 0})
hipjoint:add_child(jrl1)

jrl1:translate(1.0, 0.0, 0.0)
jrl1:rotate('z', 40)

--jrl1:rotate('z',90)

rl1 = gr.sphere('rl1')
jrl1:add_child(rl1)
rl1:scale(0.4,1.0,0.4)
rl1:translate(0.0,-1.0,0.0)
rl1:set_material(mll1)

jrl2 = gr.joint('jrl2', {-180, 0, 180}, {0, 0, 0})
jrl1:add_child(jrl2)
jrl2:translate(0.0,-2.0,0.0)
--jrl2:rotate('z',90)
jrl2:rotate('z',-30)


rl2 = gr.sphere('rl2')
jrl2:add_child(rl2)
rl2:scale(0.4,0.8,0.4)
rl2:translate(0.0,-0.8,0.0)
rl2:set_material(mll2)

jrl3 = gr.joint('jrl3', {-180, 0, 180}, {0, 0, 0})
jrl2:add_child(jrl3)
jrl3:translate(0.0,-1.4,0.0)
jrl3:rotate('z',90)

rl3 = gr.sphere('rl3')
jrl3:add_child(rl3)
rl3:scale(0.2,0.5,0.2)
rl3:translate(0.0,-0.5,0.0)
rl3:set_material(mll3)




grass = gr.material({0.1, 0.7, 0.1}, {0.0, 0.0, 0.0}, 0)



--[[
cow_poly = gr.mesh('cow', readobj('cow.obj'))
factor = 2.0/(2.76+3.637)
cow_poly:set_material(grass)
cow_poly:translate(0.0, -1.0, 0.0)
cow_poly:scale(factor, factor, factor)
cow_poly:translate(0.0, 3.637, 0.0)

rootnode:add_child(cow_poly)
--]]

cow = gr.node('the_cow')

for _, spec in pairs({
                        {'body', {0, 0, 0}, 1.0},
                        {'head', {.9, .3, 0}, 0.6},
                        {'tail', {-.94, .34, 0}, 0.2},
                        {'lfleg', {.7, -.7, -.7}, 0.3},
                        {'lrleg', {-.7, -.7, -.7}, 0.3},
                        {'rfleg', {.7, -.7, .7}, 0.3},
                        {'rrleg', {-.7, -.7, .7}, 0.3}
                     }) do
   part = gr.nh_sphere(unpack(spec))
   part:set_material(grass)
   cow:add_child(part)
end

cow:scale(2.0,2.0,2.0)
cow:rotate('y', -40)
cow:translate(0.0,-1.8,0.0)
node:add_child(cow)






mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)
mat4 = gr.material({0.7, 0.6, 1.0}, {0.5, 0.4, 0.8}, 25)


b1 = gr.nh_box('b1', {-25, -25, -40}, 20)
node:add_child(b1)
b1:set_material(mat4)


b2 = gr.nh_box('b2', {-8, -23, -10}, 15)
node:add_child(b2)
b2:scale(0.8,0.8,0.8)
b2:set_material(mat1)


require('smstdodeca')

steldodec:set_material(mat4)
steldodec:translate(-3,3,0)
steldodec:scale(0.01,0.01,0.01)
node:add_child(steldodec)


white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
orange_light = gr.light({0.0, 0.0, 150.0}, {0.7, 0.0, 0.7}, {1, 0, 0})







-- node, filename, w, h
-- eye, view, up, fov
-- ambient, lights
gr.render(node, 'sample.png', 500, 500,
          {0, 0, 16}, {0, 0, -1}, {0, 1, 0}, 80,
          {0.3, 0.3, 0.3}, {white_light,orange_light})

