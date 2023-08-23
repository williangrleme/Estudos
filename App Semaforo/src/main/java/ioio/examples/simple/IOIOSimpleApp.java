package ioio.examples.simple;

import ioio.lib.api.AnalogInput;
import ioio.lib.api.DigitalOutput;
import ioio.lib.api.IOIO;
import ioio.lib.api.PwmOutput;
import ioio.lib.api.exception.ConnectionLostException;
import ioio.lib.util.BaseIOIOLooper;
import ioio.lib.util.IOIOLooper;
import ioio.lib.util.android.IOIOActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.ToggleButton;

public class IOIOSimpleApp extends IOIOActivity {
	private TextView textView_;
	private SeekBar seekBar_;
	private ToggleButton toggleButton_;
	private ToggleButton btn1;
	private ToggleButton btn2;
	private ToggleButton btn3;
	private Button normal;
	private Button madrugada;




	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		toggleButton_ = (ToggleButton) findViewById(R.id.ToggleButton);

		toggleButton_ = (ToggleButton) findViewById(R.id.btn1);
		toggleButton_ = (ToggleButton) findViewById(R.id.btn2);
		toggleButton_ = (ToggleButton) findViewById(R.id.btn3);

		Button = findViewById(R.id.normal);
		Button = findViewById(R.id.madrugada);


		enableUi(false);
	}

	class Looper extends BaseIOIOLooper {
		private AnalogInput input_;
		private PwmOutput pwmOutput_;
		private DigitalOutput led_;
		private DigitalOutput led_1;
		private DigitalOutput led_2;
		private DigitalOutput led_3;

		@Override
		public void setup() throws ConnectionLostException {
			led_ = ioio_.openDigitalOutput(IOIO.LED_PIN, true);
			led_1 = ioio_.openDigitalOutput(6, false);
			led_2 = ioio_.openDigitalOutput(7, false);
			led_3 = ioio_.openDigitalOutput(8, false);
			input_ = ioio_.openAnalogInput(40);
			pwmOutput_ = ioio_.openPwmOutput(12, 100);
			enableUi(true);
		}

		@Override
		public void loop() throws ConnectionLostException, InterruptedException {
			setNumber(input_.read());
			pwmOutput_.setPulseWidth(500 + seekBar_.getProgress() * 2);
			led_.write(!toggleButton_.isChecked());
			Thread.sleep(10);

			normal.setOnClickListener(){
				btn1.setBackgroundResource(R.color.Green);
				led_1.write(true);
				Thread.sleep(10);
				btn1.setBackgroundResource(R.color.Black);
				led_1.write(false);
				btn2.setBackgroundResource(R.color.Yellow);
				led_2.write(true);
				Thread.sleep(10);
				btn2.setBackgroundResource(R.color.Black);
				led_2.write(false);
				btn3.setBackgroundResource(R.color.Red);
				led_3.write(true);
				Thread.sleep(10);
				btn3.setBackgroundResource(R.color.Black);
				led_3.write(false);
			}

			madrugada.setOnClickListener(){
				btn2.setBackgroundResource(R.color.Yellow);
				led_2.write(true);
				Thread.sleep(10);
				btn2.setBackgroundResource(R.color.Black);
				led_2.write(false);
				Thread.sleep(10);
			}

		}


		@Override
		public void disconnected() {
			enableUi(false);
		}
	}

	@Override
	protected IOIOLooper createIOIOLooper() {
		return new Looper();
	}

	private void enableUi(final boolean enable) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				seekBar_.setEnabled(enable);
				toggleButton_.setEnabled(enable);
				btn1.setEnabled(enable);
				btn2.setEnabled(enable);
				btn3.setEnabled(enable);
			}
		});
	}

	private void setNumber(float f) {
		final String str = String.format("%.2f", f);
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				textView_.setText(str);
			}
		});
	}
}