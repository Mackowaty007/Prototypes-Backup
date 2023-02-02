#[macro_use]
extern crate glium;

fn main() {
    #[allow(unused_imports)]
    use glium::{glutin, Surface};

    let event_loop = glutin::event_loop::EventLoop::new();
    let wb = glutin::window::WindowBuilder::new().
        with_inner_size(glium::glutin::dpi::LogicalSize::new(1000.0,1000.0)).
        with_title("Manelbrot set!");
    let cb = glutin::ContextBuilder::new();
    let display = glium::Display::new(wb, cb, &event_loop).unwrap();

    //time
    let mut t = -0.5;

    #[derive(Copy, Clone)]
    struct Vertex {
        position: [f32; 2],
        t: f32,
    }

    implement_vertex!(Vertex, position, t);

    let vertex1 = Vertex { position: [-1.0, -1.0] };
    let vertex2 = Vertex { position: [-1.0,  1.0] };
    let vertex3 = Vertex { position: [ 1.0, -1.0] };
    let vertex4 = Vertex { position: [ 1.0,  1.0] };
    let shape1  = vec![vertex1, vertex2, vertex3];
    let shape2  = vec![vertex2, vertex3, vertex4];

    let vertex_buffer1 = glium::VertexBuffer::new(&display, &shape1).unwrap();
    let vertex_buffer2 = glium::VertexBuffer::new(&display, &shape2).unwrap();
    let indices = glium::index::NoIndices(glium::index::PrimitiveType::TrianglesList);

    let vertex_shader_src = r#"
        #version 140
        in vec2 position;
        in float t;
        out vec2 my_position;
        uniform mat4 matrix;
        void main() {
            my_position = position;     // we need to set the value of each `out` variable.
            gl_Position = matrix * vec4(position, 0.0, 1.0);
        }
    "#;

    let fragment_shader_src = r#"
        #version 140
        in vec2 my_position;
        out vec4 color;

        //mandlebrot set variables
        const int accuracy = 100;

        void main() {
            //alignment
            float zx= 0.0;
            float zy= 0.0;
            int i=0;

            do
            {
            float xt=zx*zy;
            zx=zx*zx-zy*zy+my_position.x;
            zy=2.0*xt+my_position.y;
            i++;
            }
            while(i<accuracy&&(zx*zx+zy*zy)<4.0);

            color = vec4(1-float(i)/float(accuracy), 1-float(i)/float(accuracy), 1-float(i)/float(accuracy), 1.0);   // we build a vec4 from a vec2 and two floats
        }
    "#;

    let program = glium::Program::from_source(&display, vertex_shader_src, fragment_shader_src, None).unwrap();

    event_loop.run(move |event, _, control_flow| {

        match event {
            glutin::event::Event::WindowEvent { event, .. } => match event {
                glutin::event::WindowEvent::CloseRequested => {
                    *control_flow = glutin::event_loop::ControlFlow::Exit;
                    return;
                },
                _ => return,
            },
            glutin::event::Event::NewEvents(cause) => match cause {
                glutin::event::StartCause::ResumeTimeReached { .. } => (),
                glutin::event::StartCause::Init => (),
                _ => return,
            },
            _ => return,
        }

        let next_frame_time = std::time::Instant::now() + std::time::Duration::from_nanos(16_666_667);
        *control_flow = glutin::event_loop::ControlFlow::WaitUntil(next_frame_time);

        // we update `t`
        t += 0.0002;
        if t > 0.5 {
            t = -0.5;
        }

        let mut target = display.draw();
        target.clear_color(0.0, 0.0, 1.0, 1.0);

        let uniforms = uniform! {
            matrix: [
                [1.0, 0.0, 0.0, 0.0],
                [0.0, 1.0, 0.0, 0.0],
                [0.0, 0.0, 1.0, 0.0],
                [0.0, 0.0, 0.0, 1.0f32],
            ]
        };

        target.draw(&vertex_buffer1, &indices, &program, &uniforms,&Default::default()).unwrap();
        target.draw(&vertex_buffer2, &indices, &program, &uniforms,&Default::default()).unwrap();
        target.finish().unwrap();
    });
}