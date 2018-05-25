let path =
  ReactArt.Path.(
    make() |> moveTo(~x=0, ~y=0) |> lineTo(~x=10, ~y=10) |> close
  );

let transform = ReactArt.Transform.(make() |> scale(~x=2, ~y=2));

module Demo = {
  type state =
    | Hovered
    | Idle;
  let component = ReasonReact.reducerComponent("Demo");
  let make = _children => {
    ...component,
    initialState: () => Idle,
    reducer: (action, _) => ReasonReact.Update(action),
    render: ({state, send}) =>
      <ReactArt.Surface width=500 height=500>
        <ReactArt.Rectangle
          x=50
          y=50
          radius=10
          fill=(
            switch (state) {
            | Hovered =>
              LinearGradient(
                ReactArt.LinearGradient.make(
                  ~stops=[("0.5", "#0f0"), ("1", "#00f")],
                  ~x1=0,
                  ~x2=100,
                  ~y1=0,
                  ~y2=200,
                ),
              )
            | Idle => String("#f00")
            }
          )
          width=100
          height=200
          scale=(
            switch (state) {
            | Hovered => 1.2
            | Idle => 1.0
            }
          )
          onMouseOver=((_) => send(Hovered))
          onMouseOut=((_) => send(Idle))
        />
        <ReactArt.Wedge
          x=100
          y=300
          outerRadius=100
          startAngle=0
          endAngle=130
          innerRadius=80
          fill=(
            LinearGradient(
              ReactArt.LinearGradient.make(
                ~stops=[("0.5", "#ccc"), ("1", "#333")],
                ~x1=0,
                ~x2=100,
                ~y1=0,
                ~y2=200,
              ),
            )
          )
        />
        <ReactArt.Circle
          x=300
          y=100
          radius=50
          fill=(
            RadialGradient(
              ReactArt.RadialGradient.make(
                ~stops=[("0", "#fb5"), ("0.5", "#ea6"), ("1", "#fff")],
                ~fx=0,
                ~fy=0,
                ~rx=50,
                ~ry=50,
                ~cx=0,
                ~cy=0,
              ),
            )
          )
          stroke="rgba(0, 0, 0, 0.3)"
          strokeWidth=2
        />
        <ReactArt.Shape
          x=50
          y=300
          d=ReactArt.Path.(
              make()
              |> moveTo(~x=0, ~y=50)
              |> line(~x=10, ~y=10)
              |> arc(
                   ~x=50,
                   ~y=50,
                   ~rx=10,
                   ~ry=50,
                   ~outer=10,
                   ~counterClockwise=false,
                   ~rotation=300,
                 )
              |> close
            )
          fill=(String("#c40"))
        />
      </ReactArt.Surface>,
  };
};

ReactDOMRe.renderToElementWithId(<Demo />, "root");
